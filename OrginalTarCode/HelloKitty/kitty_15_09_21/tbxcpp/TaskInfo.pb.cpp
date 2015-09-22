// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: TaskInfo.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "TaskInfo.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace pb {

namespace {

const ::google::protobuf::Descriptor* Task_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Task_reflection_ = NULL;
const ::google::protobuf::Descriptor* Task_t_Task_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Task_t_Task_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_TaskInfo_2eproto() {
  protobuf_AddDesc_TaskInfo_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "TaskInfo.proto");
  GOOGLE_CHECK(file != NULL);
  Task_descriptor_ = file->message_type(0);
  static const int Task_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task, datas_),
  };
  Task_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Task_descriptor_,
      Task::default_instance_,
      Task_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Task));
  Task_t_Task_descriptor_ = Task_descriptor_->nested_type(0);
  static const int Task_t_Task_offsets_[14] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task_t_Task, tbxid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task_t_Task, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task_t_Task, title_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task_t_Task, pre_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task_t_Task, sub_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task_t_Task, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task_t_Task, pre_level_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task_t_Task, target_type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task_t_Task, target_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task_t_Task, target_content_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task_t_Task, reward_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task_t_Task, icon_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task_t_Task, guidetype_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task_t_Task, guidevalue_),
  };
  Task_t_Task_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Task_t_Task_descriptor_,
      Task_t_Task::default_instance_,
      Task_t_Task_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task_t_Task, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Task_t_Task, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Task_t_Task));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_TaskInfo_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Task_descriptor_, &Task::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Task_t_Task_descriptor_, &Task_t_Task::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_TaskInfo_2eproto() {
  delete Task::default_instance_;
  delete Task_reflection_;
  delete Task_t_Task::default_instance_;
  delete Task_t_Task_reflection_;
}

void protobuf_AddDesc_TaskInfo_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\016TaskInfo.proto\022\002pb\"\233\002\n\004Task\022\036\n\005datas\030\001"
    " \003(\0132\017.pb.Task.t_Task\032\362\001\n\006t_Task\022\r\n\005tbxi"
    "d\030\001 \002(\r\022\n\n\002id\030\002 \002(\r\022\r\n\005title\030\003 \002(\t\022\016\n\006pr"
    "e_id\030\004 \002(\t\022\013\n\003sub\030\005 \002(\r\022\014\n\004type\030\006 \002(\r\022\021\n"
    "\tpre_level\030\007 \002(\r\022\023\n\013target_type\030\010 \002(\r\022\016\n"
    "\006target\030\t \002(\t\022\026\n\016target_content\030\n \002(\t\022\016\n"
    "\006reward\030\013 \002(\t\022\014\n\004icon\030\014 \002(\t\022\021\n\tguideType"
    "\030\r \002(\r\022\022\n\nguideValue\030\016 \002(\t", 306);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "TaskInfo.proto", &protobuf_RegisterTypes);
  Task::default_instance_ = new Task();
  Task_t_Task::default_instance_ = new Task_t_Task();
  Task::default_instance_->InitAsDefaultInstance();
  Task_t_Task::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_TaskInfo_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_TaskInfo_2eproto {
  StaticDescriptorInitializer_TaskInfo_2eproto() {
    protobuf_AddDesc_TaskInfo_2eproto();
  }
} static_descriptor_initializer_TaskInfo_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Task_t_Task::kTbxidFieldNumber;
const int Task_t_Task::kIdFieldNumber;
const int Task_t_Task::kTitleFieldNumber;
const int Task_t_Task::kPreIdFieldNumber;
const int Task_t_Task::kSubFieldNumber;
const int Task_t_Task::kTypeFieldNumber;
const int Task_t_Task::kPreLevelFieldNumber;
const int Task_t_Task::kTargetTypeFieldNumber;
const int Task_t_Task::kTargetFieldNumber;
const int Task_t_Task::kTargetContentFieldNumber;
const int Task_t_Task::kRewardFieldNumber;
const int Task_t_Task::kIconFieldNumber;
const int Task_t_Task::kGuideTypeFieldNumber;
const int Task_t_Task::kGuideValueFieldNumber;
#endif  // !_MSC_VER

Task_t_Task::Task_t_Task()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Task_t_Task::InitAsDefaultInstance() {
}

Task_t_Task::Task_t_Task(const Task_t_Task& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Task_t_Task::SharedCtor() {
  _cached_size_ = 0;
  tbxid_ = 0u;
  id_ = 0u;
  title_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  pre_id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  sub_ = 0u;
  type_ = 0u;
  pre_level_ = 0u;
  target_type_ = 0u;
  target_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  target_content_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  reward_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  icon_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  guidetype_ = 0u;
  guidevalue_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Task_t_Task::~Task_t_Task() {
  SharedDtor();
}

void Task_t_Task::SharedDtor() {
  if (title_ != &::google::protobuf::internal::kEmptyString) {
    delete title_;
  }
  if (pre_id_ != &::google::protobuf::internal::kEmptyString) {
    delete pre_id_;
  }
  if (target_ != &::google::protobuf::internal::kEmptyString) {
    delete target_;
  }
  if (target_content_ != &::google::protobuf::internal::kEmptyString) {
    delete target_content_;
  }
  if (reward_ != &::google::protobuf::internal::kEmptyString) {
    delete reward_;
  }
  if (icon_ != &::google::protobuf::internal::kEmptyString) {
    delete icon_;
  }
  if (guidevalue_ != &::google::protobuf::internal::kEmptyString) {
    delete guidevalue_;
  }
  if (this != default_instance_) {
  }
}

void Task_t_Task::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Task_t_Task::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Task_t_Task_descriptor_;
}

const Task_t_Task& Task_t_Task::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_TaskInfo_2eproto();
  return *default_instance_;
}

Task_t_Task* Task_t_Task::default_instance_ = NULL;

Task_t_Task* Task_t_Task::New() const {
  return new Task_t_Task;
}

void Task_t_Task::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    tbxid_ = 0u;
    id_ = 0u;
    if (has_title()) {
      if (title_ != &::google::protobuf::internal::kEmptyString) {
        title_->clear();
      }
    }
    if (has_pre_id()) {
      if (pre_id_ != &::google::protobuf::internal::kEmptyString) {
        pre_id_->clear();
      }
    }
    sub_ = 0u;
    type_ = 0u;
    pre_level_ = 0u;
    target_type_ = 0u;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (has_target()) {
      if (target_ != &::google::protobuf::internal::kEmptyString) {
        target_->clear();
      }
    }
    if (has_target_content()) {
      if (target_content_ != &::google::protobuf::internal::kEmptyString) {
        target_content_->clear();
      }
    }
    if (has_reward()) {
      if (reward_ != &::google::protobuf::internal::kEmptyString) {
        reward_->clear();
      }
    }
    if (has_icon()) {
      if (icon_ != &::google::protobuf::internal::kEmptyString) {
        icon_->clear();
      }
    }
    guidetype_ = 0u;
    if (has_guidevalue()) {
      if (guidevalue_ != &::google::protobuf::internal::kEmptyString) {
        guidevalue_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Task_t_Task::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 tbxid = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &tbxid_)));
          set_has_tbxid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_id;
        break;
      }

      // required uint32 id = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_title;
        break;
      }

      // required string title = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_title:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_title()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->title().data(), this->title().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_pre_id;
        break;
      }

      // required string pre_id = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_pre_id:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_pre_id()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->pre_id().data(), this->pre_id().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_sub;
        break;
      }

      // required uint32 sub = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_sub:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &sub_)));
          set_has_sub();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_type;
        break;
      }

      // required uint32 type = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_type:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &type_)));
          set_has_type();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_pre_level;
        break;
      }

      // required uint32 pre_level = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_pre_level:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &pre_level_)));
          set_has_pre_level();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(64)) goto parse_target_type;
        break;
      }

      // required uint32 target_type = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_target_type:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &target_type_)));
          set_has_target_type();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(74)) goto parse_target;
        break;
      }

      // required string target = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_target:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_target()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->target().data(), this->target().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(82)) goto parse_target_content;
        break;
      }

      // required string target_content = 10;
      case 10: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_target_content:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_target_content()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->target_content().data(), this->target_content().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(90)) goto parse_reward;
        break;
      }

      // required string reward = 11;
      case 11: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_reward:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_reward()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->reward().data(), this->reward().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(98)) goto parse_icon;
        break;
      }

      // required string icon = 12;
      case 12: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_icon:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_icon()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->icon().data(), this->icon().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(104)) goto parse_guideType;
        break;
      }

      // required uint32 guideType = 13;
      case 13: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_guideType:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &guidetype_)));
          set_has_guidetype();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(114)) goto parse_guideValue;
        break;
      }

      // required string guideValue = 14;
      case 14: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_guideValue:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_guidevalue()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->guidevalue().data(), this->guidevalue().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Task_t_Task::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 tbxid = 1;
  if (has_tbxid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->tbxid(), output);
  }

  // required uint32 id = 2;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->id(), output);
  }

  // required string title = 3;
  if (has_title()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->title().data(), this->title().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->title(), output);
  }

  // required string pre_id = 4;
  if (has_pre_id()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->pre_id().data(), this->pre_id().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->pre_id(), output);
  }

  // required uint32 sub = 5;
  if (has_sub()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->sub(), output);
  }

  // required uint32 type = 6;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->type(), output);
  }

  // required uint32 pre_level = 7;
  if (has_pre_level()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(7, this->pre_level(), output);
  }

  // required uint32 target_type = 8;
  if (has_target_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(8, this->target_type(), output);
  }

  // required string target = 9;
  if (has_target()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->target().data(), this->target().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      9, this->target(), output);
  }

  // required string target_content = 10;
  if (has_target_content()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->target_content().data(), this->target_content().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      10, this->target_content(), output);
  }

  // required string reward = 11;
  if (has_reward()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->reward().data(), this->reward().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      11, this->reward(), output);
  }

  // required string icon = 12;
  if (has_icon()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->icon().data(), this->icon().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      12, this->icon(), output);
  }

  // required uint32 guideType = 13;
  if (has_guidetype()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(13, this->guidetype(), output);
  }

  // required string guideValue = 14;
  if (has_guidevalue()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->guidevalue().data(), this->guidevalue().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      14, this->guidevalue(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Task_t_Task::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 tbxid = 1;
  if (has_tbxid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->tbxid(), target);
  }

  // required uint32 id = 2;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->id(), target);
  }

  // required string title = 3;
  if (has_title()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->title().data(), this->title().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->title(), target);
  }

  // required string pre_id = 4;
  if (has_pre_id()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->pre_id().data(), this->pre_id().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->pre_id(), target);
  }

  // required uint32 sub = 5;
  if (has_sub()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->sub(), target);
  }

  // required uint32 type = 6;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->type(), target);
  }

  // required uint32 pre_level = 7;
  if (has_pre_level()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(7, this->pre_level(), target);
  }

  // required uint32 target_type = 8;
  if (has_target_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(8, this->target_type(), target);
  }

  // required string target = 9;
  if (has_target()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->target().data(), this->target().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        9, this->target(), target);
  }

  // required string target_content = 10;
  if (has_target_content()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->target_content().data(), this->target_content().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        10, this->target_content(), target);
  }

  // required string reward = 11;
  if (has_reward()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->reward().data(), this->reward().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        11, this->reward(), target);
  }

  // required string icon = 12;
  if (has_icon()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->icon().data(), this->icon().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        12, this->icon(), target);
  }

  // required uint32 guideType = 13;
  if (has_guidetype()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(13, this->guidetype(), target);
  }

  // required string guideValue = 14;
  if (has_guidevalue()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->guidevalue().data(), this->guidevalue().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        14, this->guidevalue(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Task_t_Task::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 tbxid = 1;
    if (has_tbxid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->tbxid());
    }

    // required uint32 id = 2;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }

    // required string title = 3;
    if (has_title()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->title());
    }

    // required string pre_id = 4;
    if (has_pre_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->pre_id());
    }

    // required uint32 sub = 5;
    if (has_sub()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->sub());
    }

    // required uint32 type = 6;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->type());
    }

    // required uint32 pre_level = 7;
    if (has_pre_level()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->pre_level());
    }

    // required uint32 target_type = 8;
    if (has_target_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->target_type());
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // required string target = 9;
    if (has_target()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->target());
    }

    // required string target_content = 10;
    if (has_target_content()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->target_content());
    }

    // required string reward = 11;
    if (has_reward()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->reward());
    }

    // required string icon = 12;
    if (has_icon()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->icon());
    }

    // required uint32 guideType = 13;
    if (has_guidetype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->guidetype());
    }

    // required string guideValue = 14;
    if (has_guidevalue()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->guidevalue());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Task_t_Task::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Task_t_Task* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Task_t_Task*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Task_t_Task::MergeFrom(const Task_t_Task& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_tbxid()) {
      set_tbxid(from.tbxid());
    }
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_title()) {
      set_title(from.title());
    }
    if (from.has_pre_id()) {
      set_pre_id(from.pre_id());
    }
    if (from.has_sub()) {
      set_sub(from.sub());
    }
    if (from.has_type()) {
      set_type(from.type());
    }
    if (from.has_pre_level()) {
      set_pre_level(from.pre_level());
    }
    if (from.has_target_type()) {
      set_target_type(from.target_type());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_target()) {
      set_target(from.target());
    }
    if (from.has_target_content()) {
      set_target_content(from.target_content());
    }
    if (from.has_reward()) {
      set_reward(from.reward());
    }
    if (from.has_icon()) {
      set_icon(from.icon());
    }
    if (from.has_guidetype()) {
      set_guidetype(from.guidetype());
    }
    if (from.has_guidevalue()) {
      set_guidevalue(from.guidevalue());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Task_t_Task::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Task_t_Task::CopyFrom(const Task_t_Task& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Task_t_Task::IsInitialized() const {
  if ((_has_bits_[0] & 0x00003fff) != 0x00003fff) return false;

  return true;
}

void Task_t_Task::Swap(Task_t_Task* other) {
  if (other != this) {
    std::swap(tbxid_, other->tbxid_);
    std::swap(id_, other->id_);
    std::swap(title_, other->title_);
    std::swap(pre_id_, other->pre_id_);
    std::swap(sub_, other->sub_);
    std::swap(type_, other->type_);
    std::swap(pre_level_, other->pre_level_);
    std::swap(target_type_, other->target_type_);
    std::swap(target_, other->target_);
    std::swap(target_content_, other->target_content_);
    std::swap(reward_, other->reward_);
    std::swap(icon_, other->icon_);
    std::swap(guidetype_, other->guidetype_);
    std::swap(guidevalue_, other->guidevalue_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Task_t_Task::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Task_t_Task_descriptor_;
  metadata.reflection = Task_t_Task_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Task::kDatasFieldNumber;
#endif  // !_MSC_VER

Task::Task()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Task::InitAsDefaultInstance() {
}

Task::Task(const Task& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Task::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Task::~Task() {
  SharedDtor();
}

void Task::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Task::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Task::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Task_descriptor_;
}

const Task& Task::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_TaskInfo_2eproto();
  return *default_instance_;
}

Task* Task::default_instance_ = NULL;

Task* Task::New() const {
  return new Task;
}

void Task::Clear() {
  datas_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Task::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .pb.Task.t_Task datas = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_datas:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_datas()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_datas;
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Task::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .pb.Task.t_Task datas = 1;
  for (int i = 0; i < this->datas_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->datas(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Task::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .pb.Task.t_Task datas = 1;
  for (int i = 0; i < this->datas_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->datas(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Task::ByteSize() const {
  int total_size = 0;

  // repeated .pb.Task.t_Task datas = 1;
  total_size += 1 * this->datas_size();
  for (int i = 0; i < this->datas_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->datas(i));
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Task::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Task* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Task*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Task::MergeFrom(const Task& from) {
  GOOGLE_CHECK_NE(&from, this);
  datas_.MergeFrom(from.datas_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Task::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Task::CopyFrom(const Task& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Task::IsInitialized() const {

  for (int i = 0; i < datas_size(); i++) {
    if (!this->datas(i).IsInitialized()) return false;
  }
  return true;
}

void Task::Swap(Task* other) {
  if (other != this) {
    datas_.Swap(&other->datas_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Task::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Task_descriptor_;
  metadata.reflection = Task_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)
