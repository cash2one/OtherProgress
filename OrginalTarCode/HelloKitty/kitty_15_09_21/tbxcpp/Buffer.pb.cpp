// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Buffer.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Buffer.pb.h"

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

const ::google::protobuf::Descriptor* buffer_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  buffer_reflection_ = NULL;
const ::google::protobuf::Descriptor* buffer_t_buffer_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  buffer_t_buffer_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Buffer_2eproto() {
  protobuf_AddDesc_Buffer_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Buffer.proto");
  GOOGLE_CHECK(file != NULL);
  buffer_descriptor_ = file->message_type(0);
  static const int buffer_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(buffer, datas_),
  };
  buffer_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      buffer_descriptor_,
      buffer::default_instance_,
      buffer_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(buffer, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(buffer, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(buffer));
  buffer_t_buffer_descriptor_ = buffer_descriptor_->nested_type(0);
  static const int buffer_t_buffer_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(buffer_t_buffer, tbxid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(buffer_t_buffer, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(buffer_t_buffer, type_),
  };
  buffer_t_buffer_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      buffer_t_buffer_descriptor_,
      buffer_t_buffer::default_instance_,
      buffer_t_buffer_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(buffer_t_buffer, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(buffer_t_buffer, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(buffer_t_buffer));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Buffer_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    buffer_descriptor_, &buffer::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    buffer_t_buffer_descriptor_, &buffer_t_buffer::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Buffer_2eproto() {
  delete buffer::default_instance_;
  delete buffer_reflection_;
  delete buffer_t_buffer::default_instance_;
  delete buffer_t_buffer_reflection_;
}

void protobuf_AddDesc_Buffer_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\014Buffer.proto\022\002pb\"a\n\006buffer\022\"\n\005datas\030\001 "
    "\003(\0132\023.pb.buffer.t_buffer\0323\n\010t_buffer\022\r\n\005"
    "tbxid\030\001 \002(\r\022\n\n\002id\030\002 \002(\r\022\014\n\004type\030\003 \002(\r", 117);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Buffer.proto", &protobuf_RegisterTypes);
  buffer::default_instance_ = new buffer();
  buffer_t_buffer::default_instance_ = new buffer_t_buffer();
  buffer::default_instance_->InitAsDefaultInstance();
  buffer_t_buffer::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Buffer_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Buffer_2eproto {
  StaticDescriptorInitializer_Buffer_2eproto() {
    protobuf_AddDesc_Buffer_2eproto();
  }
} static_descriptor_initializer_Buffer_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int buffer_t_buffer::kTbxidFieldNumber;
const int buffer_t_buffer::kIdFieldNumber;
const int buffer_t_buffer::kTypeFieldNumber;
#endif  // !_MSC_VER

buffer_t_buffer::buffer_t_buffer()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void buffer_t_buffer::InitAsDefaultInstance() {
}

buffer_t_buffer::buffer_t_buffer(const buffer_t_buffer& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void buffer_t_buffer::SharedCtor() {
  _cached_size_ = 0;
  tbxid_ = 0u;
  id_ = 0u;
  type_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

buffer_t_buffer::~buffer_t_buffer() {
  SharedDtor();
}

void buffer_t_buffer::SharedDtor() {
  if (this != default_instance_) {
  }
}

void buffer_t_buffer::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* buffer_t_buffer::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return buffer_t_buffer_descriptor_;
}

const buffer_t_buffer& buffer_t_buffer::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Buffer_2eproto();
  return *default_instance_;
}

buffer_t_buffer* buffer_t_buffer::default_instance_ = NULL;

buffer_t_buffer* buffer_t_buffer::New() const {
  return new buffer_t_buffer;
}

void buffer_t_buffer::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    tbxid_ = 0u;
    id_ = 0u;
    type_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool buffer_t_buffer::MergePartialFromCodedStream(
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
        if (input->ExpectTag(24)) goto parse_type;
        break;
      }

      // required uint32 type = 3;
      case 3: {
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

void buffer_t_buffer::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 tbxid = 1;
  if (has_tbxid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->tbxid(), output);
  }

  // required uint32 id = 2;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->id(), output);
  }

  // required uint32 type = 3;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->type(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* buffer_t_buffer::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 tbxid = 1;
  if (has_tbxid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->tbxid(), target);
  }

  // required uint32 id = 2;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->id(), target);
  }

  // required uint32 type = 3;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->type(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int buffer_t_buffer::ByteSize() const {
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

    // required uint32 type = 3;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->type());
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

void buffer_t_buffer::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const buffer_t_buffer* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const buffer_t_buffer*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void buffer_t_buffer::MergeFrom(const buffer_t_buffer& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_tbxid()) {
      set_tbxid(from.tbxid());
    }
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_type()) {
      set_type(from.type());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void buffer_t_buffer::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void buffer_t_buffer::CopyFrom(const buffer_t_buffer& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool buffer_t_buffer::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void buffer_t_buffer::Swap(buffer_t_buffer* other) {
  if (other != this) {
    std::swap(tbxid_, other->tbxid_);
    std::swap(id_, other->id_);
    std::swap(type_, other->type_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata buffer_t_buffer::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = buffer_t_buffer_descriptor_;
  metadata.reflection = buffer_t_buffer_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int buffer::kDatasFieldNumber;
#endif  // !_MSC_VER

buffer::buffer()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void buffer::InitAsDefaultInstance() {
}

buffer::buffer(const buffer& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void buffer::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

buffer::~buffer() {
  SharedDtor();
}

void buffer::SharedDtor() {
  if (this != default_instance_) {
  }
}

void buffer::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* buffer::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return buffer_descriptor_;
}

const buffer& buffer::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Buffer_2eproto();
  return *default_instance_;
}

buffer* buffer::default_instance_ = NULL;

buffer* buffer::New() const {
  return new buffer;
}

void buffer::Clear() {
  datas_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool buffer::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .pb.buffer.t_buffer datas = 1;
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

void buffer::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .pb.buffer.t_buffer datas = 1;
  for (int i = 0; i < this->datas_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->datas(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* buffer::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .pb.buffer.t_buffer datas = 1;
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

int buffer::ByteSize() const {
  int total_size = 0;

  // repeated .pb.buffer.t_buffer datas = 1;
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

void buffer::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const buffer* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const buffer*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void buffer::MergeFrom(const buffer& from) {
  GOOGLE_CHECK_NE(&from, this);
  datas_.MergeFrom(from.datas_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void buffer::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void buffer::CopyFrom(const buffer& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool buffer::IsInitialized() const {

  for (int i = 0; i < datas_size(); i++) {
    if (!this->datas(i).IsInitialized()) return false;
  }
  return true;
}

void buffer::Swap(buffer* other) {
  if (other != this) {
    datas_.Swap(&other->datas_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata buffer::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = buffer_descriptor_;
  metadata.reflection = buffer_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)