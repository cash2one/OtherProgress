// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: buildOption.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "buildOption.pb.h"

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

const ::google::protobuf::Descriptor* buildOption_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  buildOption_reflection_ = NULL;
const ::google::protobuf::Descriptor* buildOption_t_buildOption_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  buildOption_t_buildOption_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_buildOption_2eproto() {
  protobuf_AddDesc_buildOption_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "buildOption.proto");
  GOOGLE_CHECK(file != NULL);
  buildOption_descriptor_ = file->message_type(0);
  static const int buildOption_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(buildOption, datas_),
  };
  buildOption_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      buildOption_descriptor_,
      buildOption::default_instance_,
      buildOption_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(buildOption, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(buildOption, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(buildOption));
  buildOption_t_buildOption_descriptor_ = buildOption_descriptor_->nested_type(0);
  static const int buildOption_t_buildOption_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(buildOption_t_buildOption, tbxid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(buildOption_t_buildOption, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(buildOption_t_buildOption, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(buildOption_t_buildOption, icon_),
  };
  buildOption_t_buildOption_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      buildOption_t_buildOption_descriptor_,
      buildOption_t_buildOption::default_instance_,
      buildOption_t_buildOption_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(buildOption_t_buildOption, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(buildOption_t_buildOption, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(buildOption_t_buildOption));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_buildOption_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    buildOption_descriptor_, &buildOption::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    buildOption_t_buildOption_descriptor_, &buildOption_t_buildOption::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_buildOption_2eproto() {
  delete buildOption::default_instance_;
  delete buildOption_reflection_;
  delete buildOption_t_buildOption::default_instance_;
  delete buildOption_t_buildOption_reflection_;
}

void protobuf_AddDesc_buildOption_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\021buildOption.proto\022\002pb\"\203\001\n\013buildOption\022"
    ",\n\005datas\030\001 \003(\0132\035.pb.buildOption.t_buildO"
    "ption\032F\n\rt_buildOption\022\r\n\005tbxid\030\001 \002(\r\022\n\n"
    "\002id\030\002 \002(\r\022\014\n\004name\030\003 \002(\t\022\014\n\004icon\030\004 \002(\t", 157);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "buildOption.proto", &protobuf_RegisterTypes);
  buildOption::default_instance_ = new buildOption();
  buildOption_t_buildOption::default_instance_ = new buildOption_t_buildOption();
  buildOption::default_instance_->InitAsDefaultInstance();
  buildOption_t_buildOption::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_buildOption_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_buildOption_2eproto {
  StaticDescriptorInitializer_buildOption_2eproto() {
    protobuf_AddDesc_buildOption_2eproto();
  }
} static_descriptor_initializer_buildOption_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int buildOption_t_buildOption::kTbxidFieldNumber;
const int buildOption_t_buildOption::kIdFieldNumber;
const int buildOption_t_buildOption::kNameFieldNumber;
const int buildOption_t_buildOption::kIconFieldNumber;
#endif  // !_MSC_VER

buildOption_t_buildOption::buildOption_t_buildOption()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void buildOption_t_buildOption::InitAsDefaultInstance() {
}

buildOption_t_buildOption::buildOption_t_buildOption(const buildOption_t_buildOption& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void buildOption_t_buildOption::SharedCtor() {
  _cached_size_ = 0;
  tbxid_ = 0u;
  id_ = 0u;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  icon_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

buildOption_t_buildOption::~buildOption_t_buildOption() {
  SharedDtor();
}

void buildOption_t_buildOption::SharedDtor() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (icon_ != &::google::protobuf::internal::kEmptyString) {
    delete icon_;
  }
  if (this != default_instance_) {
  }
}

void buildOption_t_buildOption::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* buildOption_t_buildOption::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return buildOption_t_buildOption_descriptor_;
}

const buildOption_t_buildOption& buildOption_t_buildOption::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_buildOption_2eproto();
  return *default_instance_;
}

buildOption_t_buildOption* buildOption_t_buildOption::default_instance_ = NULL;

buildOption_t_buildOption* buildOption_t_buildOption::New() const {
  return new buildOption_t_buildOption;
}

void buildOption_t_buildOption::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    tbxid_ = 0u;
    id_ = 0u;
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::kEmptyString) {
        name_->clear();
      }
    }
    if (has_icon()) {
      if (icon_ != &::google::protobuf::internal::kEmptyString) {
        icon_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool buildOption_t_buildOption::MergePartialFromCodedStream(
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
        if (input->ExpectTag(26)) goto parse_name;
        break;
      }

      // required string name = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_icon;
        break;
      }

      // required string icon = 4;
      case 4: {
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

void buildOption_t_buildOption::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 tbxid = 1;
  if (has_tbxid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->tbxid(), output);
  }

  // required uint32 id = 2;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->id(), output);
  }

  // required string name = 3;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->name(), output);
  }

  // required string icon = 4;
  if (has_icon()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->icon().data(), this->icon().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->icon(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* buildOption_t_buildOption::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 tbxid = 1;
  if (has_tbxid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->tbxid(), target);
  }

  // required uint32 id = 2;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->id(), target);
  }

  // required string name = 3;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->name(), target);
  }

  // required string icon = 4;
  if (has_icon()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->icon().data(), this->icon().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->icon(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int buildOption_t_buildOption::ByteSize() const {
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

    // required string name = 3;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }

    // required string icon = 4;
    if (has_icon()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->icon());
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

void buildOption_t_buildOption::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const buildOption_t_buildOption* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const buildOption_t_buildOption*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void buildOption_t_buildOption::MergeFrom(const buildOption_t_buildOption& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_tbxid()) {
      set_tbxid(from.tbxid());
    }
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_name()) {
      set_name(from.name());
    }
    if (from.has_icon()) {
      set_icon(from.icon());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void buildOption_t_buildOption::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void buildOption_t_buildOption::CopyFrom(const buildOption_t_buildOption& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool buildOption_t_buildOption::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000000f) != 0x0000000f) return false;

  return true;
}

void buildOption_t_buildOption::Swap(buildOption_t_buildOption* other) {
  if (other != this) {
    std::swap(tbxid_, other->tbxid_);
    std::swap(id_, other->id_);
    std::swap(name_, other->name_);
    std::swap(icon_, other->icon_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata buildOption_t_buildOption::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = buildOption_t_buildOption_descriptor_;
  metadata.reflection = buildOption_t_buildOption_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int buildOption::kDatasFieldNumber;
#endif  // !_MSC_VER

buildOption::buildOption()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void buildOption::InitAsDefaultInstance() {
}

buildOption::buildOption(const buildOption& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void buildOption::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

buildOption::~buildOption() {
  SharedDtor();
}

void buildOption::SharedDtor() {
  if (this != default_instance_) {
  }
}

void buildOption::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* buildOption::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return buildOption_descriptor_;
}

const buildOption& buildOption::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_buildOption_2eproto();
  return *default_instance_;
}

buildOption* buildOption::default_instance_ = NULL;

buildOption* buildOption::New() const {
  return new buildOption;
}

void buildOption::Clear() {
  datas_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool buildOption::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .pb.buildOption.t_buildOption datas = 1;
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

void buildOption::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .pb.buildOption.t_buildOption datas = 1;
  for (int i = 0; i < this->datas_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->datas(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* buildOption::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .pb.buildOption.t_buildOption datas = 1;
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

int buildOption::ByteSize() const {
  int total_size = 0;

  // repeated .pb.buildOption.t_buildOption datas = 1;
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

void buildOption::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const buildOption* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const buildOption*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void buildOption::MergeFrom(const buildOption& from) {
  GOOGLE_CHECK_NE(&from, this);
  datas_.MergeFrom(from.datas_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void buildOption::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void buildOption::CopyFrom(const buildOption& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool buildOption::IsInitialized() const {

  for (int i = 0; i < datas_size(); i++) {
    if (!this->datas(i).IsInitialized()) return false;
  }
  return true;
}

void buildOption::Swap(buildOption* other) {
  if (other != this) {
    datas_.Swap(&other->datas_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata buildOption::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = buildOption_descriptor_;
  metadata.reflection = buildOption_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)
