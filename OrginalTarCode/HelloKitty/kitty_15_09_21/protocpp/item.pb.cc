// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: item.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "item.pb.h"

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

namespace HelloKittyMsgData {

namespace {

const ::google::protobuf::Descriptor* ReqUseItem_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ReqUseItem_reflection_ = NULL;
const ::google::protobuf::Descriptor* AckUseItemReturn_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AckUseItemReturn_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* UseItemFailType_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_item_2eproto() {
  protobuf_AddDesc_item_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "item.proto");
  GOOGLE_CHECK(file != NULL);
  ReqUseItem_descriptor_ = file->message_type(0);
  static const int ReqUseItem_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqUseItem, itemid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqUseItem, num_),
  };
  ReqUseItem_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ReqUseItem_descriptor_,
      ReqUseItem::default_instance_,
      ReqUseItem_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqUseItem, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqUseItem, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ReqUseItem));
  AckUseItemReturn_descriptor_ = file->message_type(1);
  static const int AckUseItemReturn_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AckUseItemReturn, ret_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AckUseItemReturn, reason_),
  };
  AckUseItemReturn_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AckUseItemReturn_descriptor_,
      AckUseItemReturn::default_instance_,
      AckUseItemReturn_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AckUseItemReturn, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AckUseItemReturn, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AckUseItemReturn));
  UseItemFailType_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_item_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ReqUseItem_descriptor_, &ReqUseItem::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AckUseItemReturn_descriptor_, &AckUseItemReturn::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_item_2eproto() {
  delete ReqUseItem::default_instance_;
  delete ReqUseItem_reflection_;
  delete AckUseItemReturn::default_instance_;
  delete AckUseItemReturn_reflection_;
}

void protobuf_AddDesc_item_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\nitem.proto\022\021HelloKittyMsgData\")\n\nReqUs"
    "eItem\022\016\n\006itemID\030\001 \002(\r\022\013\n\003num\030\002 \002(\r\"S\n\020Ac"
    "kUseItemReturn\022\013\n\003ret\030\001 \002(\010\0222\n\006reason\030\002 "
    "\002(\0162\".HelloKittyMsgData.UseItemFailType*"
    "}\n\017UseItemFailType\022\024\n\020Fail_Item_Illeay\020\000"
    "\022\030\n\024Fail_Item_Not_Enough\020\001\022\033\n\027Fail_Item_"
    "Level_Limited\020\002\022\035\n\031Fail_Item_Premise_Lim"
    "ited\020\003", 286);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "item.proto", &protobuf_RegisterTypes);
  ReqUseItem::default_instance_ = new ReqUseItem();
  AckUseItemReturn::default_instance_ = new AckUseItemReturn();
  ReqUseItem::default_instance_->InitAsDefaultInstance();
  AckUseItemReturn::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_item_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_item_2eproto {
  StaticDescriptorInitializer_item_2eproto() {
    protobuf_AddDesc_item_2eproto();
  }
} static_descriptor_initializer_item_2eproto_;
const ::google::protobuf::EnumDescriptor* UseItemFailType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return UseItemFailType_descriptor_;
}
bool UseItemFailType_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}


// ===================================================================

#ifndef _MSC_VER
const int ReqUseItem::kItemIDFieldNumber;
const int ReqUseItem::kNumFieldNumber;
#endif  // !_MSC_VER

ReqUseItem::ReqUseItem()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ReqUseItem::InitAsDefaultInstance() {
}

ReqUseItem::ReqUseItem(const ReqUseItem& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ReqUseItem::SharedCtor() {
  _cached_size_ = 0;
  itemid_ = 0u;
  num_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ReqUseItem::~ReqUseItem() {
  SharedDtor();
}

void ReqUseItem::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ReqUseItem::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ReqUseItem::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ReqUseItem_descriptor_;
}

const ReqUseItem& ReqUseItem::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_item_2eproto();
  return *default_instance_;
}

ReqUseItem* ReqUseItem::default_instance_ = NULL;

ReqUseItem* ReqUseItem::New() const {
  return new ReqUseItem;
}

void ReqUseItem::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    itemid_ = 0u;
    num_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ReqUseItem::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 itemID = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &itemid_)));
          set_has_itemid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_num;
        break;
      }

      // required uint32 num = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_num:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &num_)));
          set_has_num();
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

void ReqUseItem::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 itemID = 1;
  if (has_itemid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->itemid(), output);
  }

  // required uint32 num = 2;
  if (has_num()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->num(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ReqUseItem::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 itemID = 1;
  if (has_itemid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->itemid(), target);
  }

  // required uint32 num = 2;
  if (has_num()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->num(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ReqUseItem::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 itemID = 1;
    if (has_itemid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->itemid());
    }

    // required uint32 num = 2;
    if (has_num()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->num());
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

void ReqUseItem::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ReqUseItem* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ReqUseItem*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ReqUseItem::MergeFrom(const ReqUseItem& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_itemid()) {
      set_itemid(from.itemid());
    }
    if (from.has_num()) {
      set_num(from.num());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ReqUseItem::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ReqUseItem::CopyFrom(const ReqUseItem& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ReqUseItem::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void ReqUseItem::Swap(ReqUseItem* other) {
  if (other != this) {
    std::swap(itemid_, other->itemid_);
    std::swap(num_, other->num_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ReqUseItem::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ReqUseItem_descriptor_;
  metadata.reflection = ReqUseItem_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int AckUseItemReturn::kRetFieldNumber;
const int AckUseItemReturn::kReasonFieldNumber;
#endif  // !_MSC_VER

AckUseItemReturn::AckUseItemReturn()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void AckUseItemReturn::InitAsDefaultInstance() {
}

AckUseItemReturn::AckUseItemReturn(const AckUseItemReturn& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void AckUseItemReturn::SharedCtor() {
  _cached_size_ = 0;
  ret_ = false;
  reason_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AckUseItemReturn::~AckUseItemReturn() {
  SharedDtor();
}

void AckUseItemReturn::SharedDtor() {
  if (this != default_instance_) {
  }
}

void AckUseItemReturn::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AckUseItemReturn::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AckUseItemReturn_descriptor_;
}

const AckUseItemReturn& AckUseItemReturn::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_item_2eproto();
  return *default_instance_;
}

AckUseItemReturn* AckUseItemReturn::default_instance_ = NULL;

AckUseItemReturn* AckUseItemReturn::New() const {
  return new AckUseItemReturn;
}

void AckUseItemReturn::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    ret_ = false;
    reason_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AckUseItemReturn::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required bool ret = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &ret_)));
          set_has_ret();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_reason;
        break;
      }

      // required .HelloKittyMsgData.UseItemFailType reason = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_reason:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::HelloKittyMsgData::UseItemFailType_IsValid(value)) {
            set_reason(static_cast< ::HelloKittyMsgData::UseItemFailType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(2, value);
          }
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

void AckUseItemReturn::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required bool ret = 1;
  if (has_ret()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(1, this->ret(), output);
  }

  // required .HelloKittyMsgData.UseItemFailType reason = 2;
  if (has_reason()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->reason(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* AckUseItemReturn::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required bool ret = 1;
  if (has_ret()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(1, this->ret(), target);
  }

  // required .HelloKittyMsgData.UseItemFailType reason = 2;
  if (has_reason()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      2, this->reason(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int AckUseItemReturn::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required bool ret = 1;
    if (has_ret()) {
      total_size += 1 + 1;
    }

    // required .HelloKittyMsgData.UseItemFailType reason = 2;
    if (has_reason()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->reason());
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

void AckUseItemReturn::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AckUseItemReturn* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AckUseItemReturn*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AckUseItemReturn::MergeFrom(const AckUseItemReturn& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_ret()) {
      set_ret(from.ret());
    }
    if (from.has_reason()) {
      set_reason(from.reason());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AckUseItemReturn::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AckUseItemReturn::CopyFrom(const AckUseItemReturn& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AckUseItemReturn::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void AckUseItemReturn::Swap(AckUseItemReturn* other) {
  if (other != this) {
    std::swap(ret_, other->ret_);
    std::swap(reason_, other->reason_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AckUseItemReturn::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AckUseItemReturn_descriptor_;
  metadata.reflection = AckUseItemReturn_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace HelloKittyMsgData

// @@protoc_insertion_point(global_scope)
