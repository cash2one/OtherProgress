// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Param.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Param.pb.h"

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

const ::google::protobuf::Descriptor* param_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  param_reflection_ = NULL;
const ::google::protobuf::Descriptor* param_t_param_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  param_t_param_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Param_2eproto() {
  protobuf_AddDesc_Param_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Param.proto");
  GOOGLE_CHECK(file != NULL);
  param_descriptor_ = file->message_type(0);
  static const int param_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(param, datas_),
  };
  param_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      param_descriptor_,
      param::default_instance_,
      param_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(param, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(param, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(param));
  param_t_param_descriptor_ = param_descriptor_->nested_type(0);
  static const int param_t_param_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(param_t_param, tbxid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(param_t_param, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(param_t_param, intparam_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(param_t_param, strparam_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(param_t_param, strdesc_),
  };
  param_t_param_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      param_t_param_descriptor_,
      param_t_param::default_instance_,
      param_t_param_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(param_t_param, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(param_t_param, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(param_t_param));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Param_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    param_descriptor_, &param::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    param_t_param_descriptor_, &param_t_param::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Param_2eproto() {
  delete param::default_instance_;
  delete param_reflection_;
  delete param_t_param::default_instance_;
  delete param_t_param_reflection_;
}

void protobuf_AddDesc_Param_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\013Param.proto\022\002pb\"\204\001\n\005param\022 \n\005datas\030\001 \003"
    "(\0132\021.pb.param.t_param\032Y\n\007t_param\022\r\n\005tbxi"
    "d\030\001 \002(\r\022\n\n\002id\030\002 \002(\r\022\020\n\010intparam\030\003 \002(\r\022\020\n"
    "\010strparam\030\004 \002(\t\022\017\n\007strdesc\030\005 \002(\t", 152);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Param.proto", &protobuf_RegisterTypes);
  param::default_instance_ = new param();
  param_t_param::default_instance_ = new param_t_param();
  param::default_instance_->InitAsDefaultInstance();
  param_t_param::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Param_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Param_2eproto {
  StaticDescriptorInitializer_Param_2eproto() {
    protobuf_AddDesc_Param_2eproto();
  }
} static_descriptor_initializer_Param_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int param_t_param::kTbxidFieldNumber;
const int param_t_param::kIdFieldNumber;
const int param_t_param::kIntparamFieldNumber;
const int param_t_param::kStrparamFieldNumber;
const int param_t_param::kStrdescFieldNumber;
#endif  // !_MSC_VER

param_t_param::param_t_param()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void param_t_param::InitAsDefaultInstance() {
}

param_t_param::param_t_param(const param_t_param& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void param_t_param::SharedCtor() {
  _cached_size_ = 0;
  tbxid_ = 0u;
  id_ = 0u;
  intparam_ = 0u;
  strparam_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  strdesc_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

param_t_param::~param_t_param() {
  SharedDtor();
}

void param_t_param::SharedDtor() {
  if (strparam_ != &::google::protobuf::internal::kEmptyString) {
    delete strparam_;
  }
  if (strdesc_ != &::google::protobuf::internal::kEmptyString) {
    delete strdesc_;
  }
  if (this != default_instance_) {
  }
}

void param_t_param::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* param_t_param::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return param_t_param_descriptor_;
}

const param_t_param& param_t_param::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Param_2eproto();
  return *default_instance_;
}

param_t_param* param_t_param::default_instance_ = NULL;

param_t_param* param_t_param::New() const {
  return new param_t_param;
}

void param_t_param::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    tbxid_ = 0u;
    id_ = 0u;
    intparam_ = 0u;
    if (has_strparam()) {
      if (strparam_ != &::google::protobuf::internal::kEmptyString) {
        strparam_->clear();
      }
    }
    if (has_strdesc()) {
      if (strdesc_ != &::google::protobuf::internal::kEmptyString) {
        strdesc_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool param_t_param::MergePartialFromCodedStream(
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
        if (input->ExpectTag(24)) goto parse_intparam;
        break;
      }

      // required uint32 intparam = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_intparam:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &intparam_)));
          set_has_intparam();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_strparam;
        break;
      }

      // required string strparam = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_strparam:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_strparam()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->strparam().data(), this->strparam().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_strdesc;
        break;
      }

      // required string strdesc = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_strdesc:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_strdesc()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->strdesc().data(), this->strdesc().length(),
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

void param_t_param::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 tbxid = 1;
  if (has_tbxid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->tbxid(), output);
  }

  // required uint32 id = 2;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->id(), output);
  }

  // required uint32 intparam = 3;
  if (has_intparam()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->intparam(), output);
  }

  // required string strparam = 4;
  if (has_strparam()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->strparam().data(), this->strparam().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->strparam(), output);
  }

  // required string strdesc = 5;
  if (has_strdesc()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->strdesc().data(), this->strdesc().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      5, this->strdesc(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* param_t_param::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 tbxid = 1;
  if (has_tbxid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->tbxid(), target);
  }

  // required uint32 id = 2;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->id(), target);
  }

  // required uint32 intparam = 3;
  if (has_intparam()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->intparam(), target);
  }

  // required string strparam = 4;
  if (has_strparam()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->strparam().data(), this->strparam().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->strparam(), target);
  }

  // required string strdesc = 5;
  if (has_strdesc()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->strdesc().data(), this->strdesc().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->strdesc(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int param_t_param::ByteSize() const {
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

    // required uint32 intparam = 3;
    if (has_intparam()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->intparam());
    }

    // required string strparam = 4;
    if (has_strparam()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->strparam());
    }

    // required string strdesc = 5;
    if (has_strdesc()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->strdesc());
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

void param_t_param::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const param_t_param* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const param_t_param*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void param_t_param::MergeFrom(const param_t_param& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_tbxid()) {
      set_tbxid(from.tbxid());
    }
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_intparam()) {
      set_intparam(from.intparam());
    }
    if (from.has_strparam()) {
      set_strparam(from.strparam());
    }
    if (from.has_strdesc()) {
      set_strdesc(from.strdesc());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void param_t_param::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void param_t_param::CopyFrom(const param_t_param& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool param_t_param::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000001f) != 0x0000001f) return false;

  return true;
}

void param_t_param::Swap(param_t_param* other) {
  if (other != this) {
    std::swap(tbxid_, other->tbxid_);
    std::swap(id_, other->id_);
    std::swap(intparam_, other->intparam_);
    std::swap(strparam_, other->strparam_);
    std::swap(strdesc_, other->strdesc_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata param_t_param::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = param_t_param_descriptor_;
  metadata.reflection = param_t_param_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int param::kDatasFieldNumber;
#endif  // !_MSC_VER

param::param()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void param::InitAsDefaultInstance() {
}

param::param(const param& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void param::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

param::~param() {
  SharedDtor();
}

void param::SharedDtor() {
  if (this != default_instance_) {
  }
}

void param::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* param::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return param_descriptor_;
}

const param& param::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Param_2eproto();
  return *default_instance_;
}

param* param::default_instance_ = NULL;

param* param::New() const {
  return new param;
}

void param::Clear() {
  datas_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool param::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .pb.param.t_param datas = 1;
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

void param::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .pb.param.t_param datas = 1;
  for (int i = 0; i < this->datas_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->datas(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* param::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .pb.param.t_param datas = 1;
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

int param::ByteSize() const {
  int total_size = 0;

  // repeated .pb.param.t_param datas = 1;
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

void param::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const param* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const param*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void param::MergeFrom(const param& from) {
  GOOGLE_CHECK_NE(&from, this);
  datas_.MergeFrom(from.datas_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void param::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void param::CopyFrom(const param& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool param::IsInitialized() const {

  for (int i = 0; i < datas_size(); i++) {
    if (!this->datas(i).IsInitialized()) return false;
  }
  return true;
}

void param::Swap(param* other) {
  if (other != this) {
    datas_.Swap(&other->datas_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata param::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = param_descriptor_;
  metadata.reflection = param_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)
