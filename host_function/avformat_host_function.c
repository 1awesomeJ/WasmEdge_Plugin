#include <stdlib.h>

#include <libavformat/avformat.h>
#include <wasmedge/wasmedge.h>

WasmEdge_Result fetch_video_resolution(void *Data, const WasmEdge_CallingFrameContext *FrameCxt, const WasmEdge_Value *In, WasmEdge_Value *Out) {
	AVFormatContext *format_ctx = NULL;
	const char * file_path = WasmEdge_ValueGetExternRef(In[0]);

	if (avformat_open_input(&format_ctx, file_path, NULL, NULL) != 0)
		return WasmEdge_Result_Fail;

	int video_stream_index = -1;

	avformat_find_stream_info(format_ctx, NULL);
	for (int i = 0; i < format_ctx->nb_streams; i++) {
		if (format_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
			video_stream_index = i;
			break;
		}
	}

	if (video_stream_index == -1)
		return WasmEdge_Result_Fail;  /*no video stream found in the given file*/

	WasmEdge_Value resolution = WasmEdge_ValueGenI32(format_ctx->streams[video_stream_index]->codecpar->height);
	Out[0] = resolution;

	avformat_close_input(&format_ctx);
	
	return WasmEdge_Result_Success;
}

WasmEdge_ModuleInstanceContext* CreateModule (const struct WasmEdge_ModuleDescriptor *Desc) {
	
	WasmEdge_String ModuleName = WasmEdge_StringCreateByCString("wasmedge_ffmpeg_plugin_module");
	WasmEdge_ModuleInstanceContext *Mod = WasmEdge_ModuleInstanceCreate(ModuleName);
	WasmEdge_StringDelete(ModuleName);
	WasmEdge_String FuncName;
	WasmEdge_FunctionTypeContext *FType;
	WasmEdge_FunctionInstanceContext *FuncCxt;
	enum WasmEdge_ValType ParamType[1] = {WasmEdge_ValType_ExternRef};
	enum WasmEdge_ValType ReturnType[1] = {WasmEdge_ValType_I32};
	
	FType = WasmEdge_FunctionTypeCreate(ParamType, 1, ReturnType, 1);
	FuncName = WasmEdge_StringCreateByCString("fetch_video_resolution");
	FuncCxt = WasmEdge_FunctionInstanceCreate(FType, fetch_video_resolution, NULL, 0);
	WasmEdge_ModuleInstanceAddFunction(Mod, FuncName, FuncCxt);
	WasmEdge_StringDelete(FuncName);
	WasmEdge_FunctionTypeDelete(FType);
	
	return Mod;
}
static WasmEdge_ModuleDescriptor ModuleDesc[] = {{
	.Name = "wasmedge_ffmpeg_plugin_module",
	.Description = "This module contains wrapper functions with C API for ffmpeg functions",
	.Create = CreateModule,
}};

static WasmEdge_PluginDescriptor Desc[] = {{
	.Name = "fetch_video_resolution",
	.Description = "wasmedge plugin for ffmpeg's avformat_find_stream_info() function",
	.APIVersion = WasmEdge_Plugin_CurrentAPIVersion,
	.Version =
		{
			.Major = 0,
			.Minor = 1,
			.Patch = 0,
			.Build = 0,
		},
	.ModuleCount = 1,
	.ProgramOptionCount = 0,
	.ModuleDescriptions = ModuleDesc,
	.ProgramOptions = NULL,
}};
