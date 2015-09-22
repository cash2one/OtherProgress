// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: toy.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "toy.pb.h"

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

const ::google::protobuf::Descriptor* ReqOpToy_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ReqOpToy_reflection_ = NULL;
const ::google::protobuf::Descriptor* AckToy_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AckToy_reflection_ = NULL;
const ::google::protobuf::Descriptor* AckRandToy_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AckRandToy_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* OpToyType_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_toy_2eproto() {
  protobuf_AddDesc_toy_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "toy.proto");
  GOOGLE_CHECK(file != NULL);
  ReqOpToy_descriptor_ = file->message_type(0);
  static const int ReqOpToy_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqOpToy, optype_),
  };
  ReqOpToy_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ReqOpToy_descriptor_,
      ReqOpToy::default_instance_,
      ReqOpToy_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqOpToy, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqOpToy, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ReqOpToy));
  AckToy_descriptor_ = file->message_type(1);
  static const int AckToy_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AckToy, toyid_),
  };
  AckToy_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AckToy_descriptor_,
      AckToy::default_instance_,
      AckToy_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AckToy, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AckToy, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AckToy));
  AckRandToy_descriptor_ = file->message_type(2);
  static const int AckRandToy_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AckRandToy, randtoyid_),
  };
  AckRandToy_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AckRandToy_descriptor_,
      AckRandToy::default_instance_,
      AckRandToy_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AckRandToy, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AckRandToy, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AckRandToy));
  OpToyType_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_toy_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ReqOpToy_descriptor_, &ReqOpToy::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AckToy_descriptor_, &AckToy::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AckRandToy_descriptor_, &AckRandToy::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_toy_2eproto() {
  delete ReqOpToy::default_instance_;
  delete ReqOpToy_reflection_;
  delete AckToy::default_instance_;
  delete AckToy_reflection_;
  delete AckRandToy::default_instance_;
  delete AckRandToy_reflection_;
}

void protobuf_AddDesc_toy_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\ttoy.proto\022\021HelloKittyMsgData\"8\n\010ReqOpT"
    "oy\022,\n\006optype\030\001 \002(\0162\034.HelloKittyMsgData.O"
    "pToyType\"\027\n\006AckToy\022\r\n\005toyid\030\001 \003(\r\"\037\n\nAck"
    "RandToy\022\021\n\trandtoyid\030\001 \002(\r*&\n\tOpToyType\022"
    "\013\n\007OTT_Req\020\000\022\014\n\010OTT_Rand\020\001", 186);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "toy.proto", &protobuf_RegisterTypes);
  ReqOpToy::default_instance_ = new ReqOpToy();
  AckToy::default_instance_ = new AckToy();
  AckRandToy::default_instance_ = new AckRandToy();
  ReqOpToy::default_instance_->InitAsDefaultInstance();
  AckToy::default_instance_->InitAsDefaultInstance();
  AckRandToy::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_toy_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_toy_2eproto {
  StaticDescriptorInitializer_toy_2eproto() {
    protobuf_AddDesc_toy_2eproto();
  }
} static_descriptor_initializer_toy_2eproto_;
const ::google::protobuf::EnumDescriptor* OpToyType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return OpToyType_descriptor_;
}
bool OpToyType_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}


// ===================================================================

#ifndef _MSC_VER
const int ReqOpToy::kOptypeFieldNumber;
#endif  // !_MSC_VER

ReqOpToy::ReqOpToy()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ReqOpToy::InitAsDefaultInstance() {
}

ReqOpToy::ReqOpToy(const ReqOpToy& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ReqOpToy::SharedCtor() {
  _cached_size_ = 0;
  optype_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ReqOpToy::~ReqOpToy() {
  SharedDtor();
}

void ReqOpToy::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ReqOpToy::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ReqOpToy::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ReqOpToy_descriptor_;
}

const ReqOpToy& ReqOpToy::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_toy_2eproto();
  return *default_instance_;
}

ReqOpToy* ReqOpToy::default_instance_ = NULL;

ReqOpToy* ReqOpToy::New() const {
  return new ReqOpToy;
}

void ReqOpToy::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    optype_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ReqOpToy::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .HelloKittyMsgData.OpToyType optype = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::HelloKittyMsgData::OpToyType_IsValid(value)) {
            set_optype(static_cast< ::HelloKittyMsgData::OpToyType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
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

void ReqOpToy::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .HelloKittyMsgData.OpToyType optype = 1;
  if (has_optype()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->optype(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ReqOpToy::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required .HelloKittyMsgData.OpToyType optype = 1;
  if (has_optype()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->optype(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ReqOpToy::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .HelloKittyMsgData.OpToyType optype = 1;
    if (has_optype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->optype());
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

void ReqOpToy::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ReqOpToy* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ReqOpToy*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ReqOpToy::MergeFrom(const ReqOpToy& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_optype()) {
      set_optype(from.optype());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ReqOpToy::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ReqOpToy::CopyFrom(const ReqOpToy& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ReqOpToy::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void ReqOpToy::Swap(ReqOpToy* other) {
  if (other != this) {
    std::swap(optype_, other->optype_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ReqOpToy::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ReqOpToy_descriptor_;
  metadata.reflection = ReqOpToy_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int AckToy::kToyidFieldNumber;
#endif  // !_MSC_VER

AckToy::AckToy()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void AckToy::InitAsDefaultInstance() {
}

AckToy::AckToy(const AckToy& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void AckToy::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AckToy::~AckToy() {
  SharedDtor();
}

void AckToy::SharedDtor() {
  if (this != default_instance_) {
  }
}

void AckToy::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AckToy::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AckToy_descriptor_;
}

const AckToy& AckToy::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_toy_2eproto();
  return *default_instance_;
}

AckToy* AckToy::default_instance_ = NULL;

AckToy* AckToy::New() const {
  return new AckToy;
}

void AckToy::Clear() {
  toyid_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AckToy::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated uint32 toyid = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_toyid:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 8, input, this->mutable_toyid())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_toyid())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(8)) goto parse_toyid;
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

void AckToy::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated uint32 toyid = 1;
  for (int i = 0; i < this->toyid_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      1, this->toyid(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* AckToy::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated uint32 toyid = 1;
  for (int i = 0; i < this->toyid_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(1, this->toyid(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int AckToy::ByteSize() const {
  int total_size = 0;

  // repeated uint32 toyid = 1;
  {
    int data_size = 0;
    for (int i = 0; i < this->toyid_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->toyid(i));
    }
    total_size += 1 * this->toyid_size() + data_size;
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

void AckToy::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AckToy* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AckToy*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AckToy::MergeFrom(const AckToy& from) {
  GOOGLE_CHECK_NE(&from, this);
  toyid_.MergeFrom(from.toyid_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AckToy::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AckToy::CopyFrom(const AckToy& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AckToy::IsInitialized() const {

  return true;
}

void AckToy::Swap(AckToy* other) {
  if (other != this) {
    toyid_.Swap(&other->toyid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AckToy::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AckToy_descriptor_;
  metadata.reflection = AckToy_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int AckRandToy::kRandtoyidFieldNumber;
#endif  // !_MSC_VER

AckRandToy::AckRandToy()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void AckRandToy::InitAsDefaultInstance() {
}

AckRandToy::AckRandToy(const AckRandToy& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void AckRandToy::SharedCtor() {
  _cached_size_ = 0;
  randtoyid_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AckRandToy::~AckRandToy() {
  SharedDtor();
}

void AckRandToy::SharedDtor() {
  if (this != default_instance_) {
  }
}

void AckRandToy::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AckRandToy::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AckRandToy_descriptor_;
}

const AckRandToy& AckRandToy::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_toy_2eproto();
  return *default_instance_;
}

AckRandToy* AckRandToy::default_instance_ = NULL;

AckRandToy* AckRandToy::New() const {
  return new AckRandToy;
}

void AckRandToy::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    randtoyid_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AckRandToy::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 randtoyid = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &randtoyid_)));
          set_has_randtoyid();
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

void AckRandToy::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 randtoyid = 1;
  if (has_randtoyid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->randtoyid(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* AckRandToy::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 randtoyid = 1;
  if (has_randtoyid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->randtoyid(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int AckRandToy::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 randtoyid = 1;
    if (has_randtoyid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->randtoyid());
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

void AckRandToy::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AckRandToy* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AckRandToy*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AckRandToy::MergeFrom(const AckRandToy& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_randtoyid()) {
      set_randtoyid(from.randtoyid());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AckRandToy::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AckRandToy::CopyFrom(const AckRandToy& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AckRandToy::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void AckRandToy::Swap(AckRandToy* other) {
  if (other != this) {
    std::swap(randtoyid_, other->randtoyid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AckRandToy::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AckRandToy_descriptor_;
  metadata.reflection = AckRandToy_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace HelloKittyMsgData

// @@protoc_insertion_point(global_scope)
