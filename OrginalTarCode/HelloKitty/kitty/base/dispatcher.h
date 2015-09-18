#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#include "Fir.h"
#include "nullcmd.h"
#include "zFunctor.h"
#include "zNoncopyable.h"
#include <assert.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <map>
#include <iostream>

using namespace std;

namespace Fir {

	template <typename T>
		class MessageCallback : private zNoncopyable {
			public:
				virtual ~MessageCallback() {};
				virtual bool exec(T* owner, const _null_cmd_ *cmd, const unsigned int cmdlen) const = 0;
		};
    
    template <typename T>
		class ProtoMessageCallback : private zNoncopyable {
			public:
				virtual ~ProtoMessageCallback() {};
				virtual bool exec(T* owner, const google::protobuf::Message *protoMessage) const = 0;
		};



	template <typename T, typename cmd_type>
		class CmdCallback : public MessageCallback<T> {
			public:
				typedef Fir::Functor<bool, Fir::Seq<T*, const cmd_type*, const unsigned int> > Function;
				CmdCallback(const Function& callback) : _callback(callback) {}
				virtual bool exec(T* owner, const _null_cmd_ *cmd, const unsigned int cmdlen) const
				{
					if (cmd) {
						const cmd_type* concrete = (const cmd_type*)cmd;
						if (cmdlen < sizeof(cmd_type))
						{
#ifdef _ALL_SUPER_GM
							Fir::logger->error("接收到的消息长度非法,cmd->_cmdid:%hu", cmd->_id);
#endif
							return false;
						}
						return _callback(owner, concrete, cmdlen);
					}
					return false;
				}

			private:
				Function _callback;
		};
    
    template <typename T,typename proto_type>
		class ProtoCmdCallback : public ProtoMessageCallback<T> {
			public:
				typedef Fir::Functor<bool, Fir::Seq<T*, const proto_type*> > ProtoFunction;
				ProtoCmdCallback(const ProtoFunction& callback) : _callback(callback) {}
				virtual bool exec(T* owner, const google::protobuf::Message *protoMessage) const
				{
					if (protoMessage)
                    {
                        const proto_type *message = (const proto_type*)protoMessage;
                        if(message)
                        {
                            return _callback(owner, message);
                        }
					}
					return false;
				}

			private:
				ProtoFunction _callback;
		};


	template <typename T>
		class Dispatcher {
			private:

			public:
				Dispatcher(const std::string name) : _name(name){}
				virtual ~Dispatcher() 
				{
					for (unsigned int i=0; i<_callback_tables.size(); i++)
						SAFE_DELETE(_callback_tables[i]);
					_callback_tables.clear();
				}

				bool dispatch(T* owner, const _null_cmd_ *cmd, const unsigned int cmdlen)
				{
#ifdef _ZJW_DEBUG
					Fir::logger->debug("dispatch cmd %d, cmdlen %d", cmd->_id, cmdlen);
#endif
#ifdef _DEBUG_WCX
//					Fir::logger->debug("dispatch cmd %d, cmdlen %d", cmd->_id, cmdlen);
#endif
					if (!cmd || !cmdlen)
						return false;

					if (cmd->_id >= _callback_tables.size())
						return false;
					if (_callback_tables[cmd->_id]) return _callback_tables[cmd->_id]->exec(owner, cmd, cmdlen);
					return false;
				}

				template <typename cmd_type>
					void func_reg(const typename CmdCallback<T, cmd_type>::Function &func)
					{ 
#ifdef _DEBUG_WCX
						Fir::logger->debug("func_reg %d ", cmd_type::ID);
#endif						
#ifdef _ALL_SUPER_GM
						_null_cmd_ check_cmd(cmd_type::ID);
						if (check_cmd.cmd == 0)
						{
							Fir::logger->error("错误的消息id:%u,(%s,%u)",cmd_type::ID,__PRETTY_FUNCTION__,__LINE__);
						}
						assert(check_cmd.cmd);
#endif
						if (cmd_type::ID >= _callback_tables.size())
							_callback_tables.resize(cmd_type::ID+100);

						_callback_tables[cmd_type::ID] = new CmdCallback<T, cmd_type>(func);
					}

				template <typename cmd_type, long id>
					void func_reg(const typename CmdCallback<T, cmd_type>::Function &func)
					{ 
#ifdef _DEBUG_WCX
						Fir::logger->debug("func_reg %u ", id);
#endif			
#ifdef _ALL_SUPER_GM
						_null_cmd_ check_cmd(id);
						if (check_cmd.cmd == 0)
						{
							Fir::logger->error("错误的消息id:%u,(%s,%u)",id,__PRETTY_FUNCTION__,__LINE__);
						}
						assert(check_cmd.cmd);
#endif
						if (id >= _callback_tables.size())
							_callback_tables.resize(id+100);
						
						_callback_tables[id] = new CmdCallback<T, cmd_type>(func);
					}

			private:
				std::vector< MessageCallback<T>* > _callback_tables;
				std::string _name;
		};
    
    template <typename T>
		class ProtoDispatcher {
			private:

			public:
				ProtoDispatcher(const std::string name) : _name(name){}
				virtual ~ProtoDispatcher() 
				{
                    typename CallbackMap::iterator iter = _callback_tables.begin();
                    while(iter != _callback_tables.end())
                    {
                        SAFE_DELETE(iter->second);
                        ++iter;
                    }
					_callback_tables.clear();
				}

				bool dispatch(T* owner,const google::protobuf::Message *message)
				{
                    if(!owner || !message)
                    {
                        return false;
                    }
                    typename CallbackMap::const_iterator iter = _callback_tables.find(message->GetDescriptor());
                    if(iter == _callback_tables.end())
                    {
                        return false;
                    }
                    
                    return _callback_tables[message->GetDescriptor()]->exec(owner,message);
				}
                
                template<typename proto_cmd>
				void func_reg(const typename ProtoCmdCallback<T,proto_cmd>::ProtoFunction &func)
				{
                    typename CallbackMap::const_iterator iter = _callback_tables.find(proto_cmd::descriptor());
                    if(iter != _callback_tables.end())
                    {
                        return;
                    }
                    _callback_tables[proto_cmd::descriptor()] = new ProtoCmdCallback<T,proto_cmd>(func);
				}
			private:
                typedef std::map<const google::protobuf::Descriptor*, ProtoMessageCallback<T>*> CallbackMap;
				CallbackMap _callback_tables;
				std::string _name;
		};


}

#endif
