#ifndef _SceneCommand_h_
#define _SceneCommand_h_

#include "zNullCmd.h"
#include "messageType.h"

#pragma pack(1)

namespace CMD
{

	namespace SCENE
	{
#if 0
		const BYTE CMD_LOGIN = 1;

		namespace ID
		{
			enum
			{
				scene_cmd_min = 1,
				t_Refresh_LoginScene,
				t_Scene_ForwardScene, //gate to scene user cmd
				t_User_FromScene,  //scene to gate to user
				t_StartOKSceneGate,//scenetask ok
				scene_cmd_max = 65535,
			};
		};
#endif   
        struct SceneNull : t_NullCmd
        {
            SceneNull()
            {
                cmd = SCENECMD;
            }
        };

		const BYTE PARA_LOGIN = 1;
		struct t_LoginScene : SceneNull 
		{
			WORD wdServerID;
			WORD wdServerType;
			t_LoginScene()
            {
                para = PARA_LOGIN;
                wdServerID = 0;
                wdServerType = 0;
            }
		};

        const BYTE PARA_REFRESH_LOGIN_SCENE = 2;
        struct t_Refresh_LoginScene : SceneNull 
		{
			QWORD charid;
			DWORD dwSceneTempID;
			t_Refresh_LoginScene()
            {
                para = PARA_REFRESH_LOGIN_SCENE;
                charid = 0;
                dwSceneTempID = 0;
            }
		};

        const BYTE PARA_FORWARD_SCENE = 3;
        struct t_Scene_ForwardScene : SceneNull
		{
			QWORD charid;
			DWORD accid;
			DWORD size;
			char data[0];

			t_Scene_ForwardScene()
			{
			    para = PARA_FORWARD_SCENE;
                charid = 0;
                accid = 0;
                size = 0;
			}
		};
        
        const BYTE PARA_SCENE_USER = 4;
        struct t_User_FromScene : SceneNull
		{
			QWORD charid;
			DWORD size;
			char data[0];

			t_User_FromScene()
			{
                para = PARA_SCENE_USER;
                charid = 0;
                size = 0;
			}
		};
        
        const BYTE PARA_START_OK_SCENE_GATE = 5;
        struct t_StartOKSceneGate : SceneNull
		{
			t_StartOKSceneGate()
			{
                para = PARA_START_OK_SCENE_GATE;
			}
		};

	};
};

#pragma pack()

#endif
