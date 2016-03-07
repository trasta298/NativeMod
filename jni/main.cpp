#include <Substrate.h>
#include <dlfcn.h>
#include <jni.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <android/log.h>

#include "minecraftpe/common/Common.h"
#include "minecraftpe/client/gui/Gui.h"

/*バージョンを変更する*/
std::string(*_Common_getGameVersionString)(Common*);
std::string Common_getGameVersionString(Common *common){
		std::stringstream stringstream;
		stringstream<<_Common_getGameVersionString(common)<<" EX";
		return stringstream.str();
}

/*メッセージ出力処理*/
Gui *gui=NULL;

void(*Gui_displayClientMessage)(Gui*,std::string const&);
void(*Gui_displayChatMessage)(Gui*,std::string const&,std::string const&);
void(*Gui_displaySystemMessage)(Gui*,std::string const&);
void(*Gui_showTipMessage)(Gui*,std::string const&);
void(*Gui_showPopupNotice)(Gui*,std::string const&,std::string const&);
void(*Gui_postError)(Gui*,int);

void displayClientMessage(std::string const&);
void displayChatMessage(std::string const&,std::string const&);
void displaySystemMessage(std::string const&);
void showTipMessage(std::string const&);
void showPopupNotice(std::string const&,std::string const&);
void postError(int);

void (*_Gui_render)(Gui*,float,bool,int,int);
void Gui_render(Gui* _gui,float _float,bool _bool,int _int_1,int _int_2){
	gui=_gui;
	_Gui_render(_gui,_float,_bool,_int_1,0);
}

void displayClientMessage(std::string const& _string){
	if(gui!=NULL){
		Gui_displayClientMessage(gui,_string);
	}
}
void displayChatMessage(std::string const& _string_1,std::string const& _string_2){
	if(gui!=NULL){
		Gui_displayChatMessage(gui,_string_1,_string_2);
	}
}
void displaySystemMessage(std::string const& _string){
	if(gui!=NULL){
		Gui_displaySystemMessage(gui,_string);
	}
}
void showTipMessage(std::string const&_string){
	if(gui!=NULL){
		Gui_showTipMessage(gui,_string);
	}
}
void showPopupNotice(std::string const&_string_1,std::string const&_string_2){
	if(gui!=NULL){
		Gui_showPopupNotice(gui,_string_1,_string_2);
	}
}
void postError(int _int){
	if(gui!=NULL){
		Gui_postError(gui,_int);
	}
}

/*Example*/
//displayClientMessage("Message");
//displayChatMessage("Name","Message!");
//displaySystemMessage("SystemMessage");
//showTipMessage("TipMessage");
//showPopupNotice("Ping","Pong");
//postError(0);


JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved){
	MSHookFunction((void*)&Common::getGameVersionString,(void*)&Common_getGameVersionString,(void**)&_Common_getGameVersionString);
	MSHookFunction((void*)&Gui::render,(void*)&Gui_render,(void**)&_Gui_render);
	Gui_displayClientMessage=(void(*)(Gui*,std::string const&))&Gui::displayClientMessage;
	Gui_displayChatMessage=(void(*)(Gui*,std::string const&,std::string const&))&Gui::displayChatMessage;
	Gui_displaySystemMessage=(void(*)(Gui*,std::string const&))&Gui::displaySystemMessage;
	Gui_showTipMessage=(void(*)(Gui*,std::string const&))&Gui::showTipMessage;
	Gui_showPopupNotice=(void(*)(Gui*,std::string const&,std::string const&))&Gui::showPopupNotice;
	Gui_postError=(void(*)(Gui*,int))&Gui::postError;
	return JNI_VERSION_1_2;
}