// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Paper.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Paper.pb.h"

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

const ::google::protobuf::Descriptor* Paper_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Paper_reflection_ = NULL;
const ::google::protobuf::Descriptor* Paper_t_Paper_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Paper_t_Paper_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Paper_2eproto() {
  protobuf_AddDesc_Paper_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Paper.proto");
  GOOGLE_CHECK(file != NULL);
  Paper_descriptor_ = file->message_type(0);
  static const int Paper_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Paper, datas_),
  };
  Paper_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Paper_descriptor_,
      Paper::default_instance_,
      Paper_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Paper, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Paper, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Paper));
  Paper_t_Paper_descriptor_ = Paper_descriptor_->nested_type(0);
  static const int Paper_t_Paper_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Paper_t_Paper, tbxid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Paper_t_Paper, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Paper_t_Paper, material_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Paper_t_Paper, produce_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Paper_t_Paper, price_),
  };
  Paper_t_Paper_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Paper_t_Paper_descriptor_,
      Paper_t_Paper::default_instance_,
      Paper_t_Paper_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Paper_t_Paper, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Paper_t_Paper, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Paper_t_Paper));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Paper_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Paper_descriptor_, &Paper::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Paper_t_Paper_descriptor_, &Paper_t_Paper::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Paper_2eproto() {
  delete Paper::default_instance_;
  delete Paper_reflection_;
  delete Paper_t_Paper::default_instance_;
  delete Paper_t_Paper_reflection_;
}

void protobuf_AddDesc_Paper_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\013Paper.proto\022\002pb\"\201\001\n\005Paper\022 \n\005datas\030\001 \003"
    "(\0132\021.pb.Paper.t_Paper\032V\n\007t_Paper\022\r\n\005tbxi"
    "d\030\001 \002(\r\022\n\n\002id\030\002 \002(\r\022\020\n\010material\030\003 \002(\t\022\017\n"
    "\007produce\030\004 \002(\t\022\r\n\005price\030\005 \002(\r", 149);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Paper.proto", &protobuf_RegisterTypes);
  Paper::default_instance_ = new Paper();
  Paper_t_Paper::default_instance_ = new Paper_t_Paper();
  Paper::default_instance_->InitAsDefaultInstance();
  Paper_t_Paper::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Paper_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Paper_2eproto {
  StaticDescriptorInitializer_Paper_2eproto() {
    protobuf_AddDesc_Paper_2eproto();
  }
} static_descriptor_initializer_Paper_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Paper_t_Paper::kTbxidFieldNumber;
const int Paper_t_Paper::kIdFieldNumber;
const int Paper_t_Paper::kMaterialFieldNumber;
const int Paper_t_Paper::kProduceFieldNumber;
const int Paper_t_Paper::kPriceFieldNumber;
#endif  // !_MSC_VER

Paper_t_Paper::Paper_t_Paper()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Paper_t_Paper::InitAsDefaultInstance() {
}

Paper_t_Paper::Paper_t_Paper(const Paper_t_Paper& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Paper_t_Paper::SharedCtor() {
  _cached_size_ = 0;
  tbxid_ = 0u;
  id_ = 0u;
  material_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  produce_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  price_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Paper_t_Paper::~Paper_t_Paper() {
  SharedDtor();
}

void Paper_t_Paper::SharedDtor() {
  if (material_ != &::google::protobuf::internal::kEmptyString) {
    delete material_;
  }
  if (produce_ != &::google::protobuf::internal::kEmptyString) {
    delete produce_;
  }
  if (this != default_instance_) {
  }
}

void Paper_t_Paper::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Paper_t_Paper::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Paper_t_Paper_descriptor_;
}

const Paper_t_Paper& Paper_t_Paper::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Paper_2eproto();
  return *default_instance_;
}

Paper_t_Paper* Paper_t_Paper::default_instance_ = NULL;

Paper_t_Paper* Paper_t_Paper::New() const {
  return new Paper_t_Paper;
}

void Paper_t_Paper::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    tbxid_ = 0u;
    id_ = 0u;
    if (has_material()) {
      if (material_ != &::google::protobuf::internal::kEmptyString) {
        material_->clear();
      }
    }
    if (has_produce()) {
      if (produce_ != &::google::protobuf::internal::kEmptyString) {
        produce_->clear();
      }
    }
    price_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Paper_t_Paper::MergePartialFromCodedStream(
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
        if (input->ExpectTag(26)) goto parse_material;
        break;
      }

      // required string material = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_material:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_material()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->material().data(), this->material().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_produce;
        break;
      }

      // required string produce = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_produce:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_produce()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->produce().data(), this->produce().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_price;
        break;
      }

      // required uint32 price = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_price:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &price_)));
          set_has_price();
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

void Paper_t_Paper::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 tbxid = 1;
  if (has_tbxid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->tbxid(), output);
  }

  // required uint32 id = 2;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->id(), output);
  }

  // required string material = 3;
  if (has_material()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->material().data(), this->material().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->material(), output);
  }

  // required string produce = 4;
  if (has_produce()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->produce().data(), this->produce().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->produce(), output);
  }

  // required uint32 price = 5;
  if (has_price()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->price(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Paper_t_Paper::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 tbxid = 1;
  if (has_tbxid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->tbxid(), target);
  }

  // required uint32 id = 2;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->id(), target);
  }

  // required string material = 3;
  if (has_material()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->material().data(), this->material().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->material(), target);
  }

  // required string produce = 4;
  if (has_produce()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->produce().data(), this->produce().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->produce(), target);
  }

  // required uint32 price = 5;
  if (has_price()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->price(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Paper_t_Paper::ByteSize() const {
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

    // required string material = 3;
    if (has_material()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->material());
    }

    // required string produce = 4;
    if (has_produce()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->produce());
    }

    // required uint32 price = 5;
    if (has_price()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->price());
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

void Paper_t_Paper::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Paper_t_Paper* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Paper_t_Paper*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Paper_t_Paper::MergeFrom(const Paper_t_Paper& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_tbxid()) {
      set_tbxid(from.tbxid());
    }
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_material()) {
      set_material(from.material());
    }
    if (from.has_produce()) {
      set_produce(from.produce());
    }
    if (from.has_price()) {
      set_price(from.price());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Paper_t_Paper::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Paper_t_Paper::CopyFrom(const Paper_t_Paper& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Paper_t_Paper::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000001f) != 0x0000001f) return false;

  return true;
}

void Paper_t_Paper::Swap(Paper_t_Paper* other) {
  if (other != this) {
    std::swap(tbxid_, other->tbxid_);
    std::swap(id_, other->id_);
    std::swap(material_, other->material_);
    std::swap(produce_, other->produce_);
    std::swap(price_, other->price_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Paper_t_Paper::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Paper_t_Paper_descriptor_;
  metadata.reflection = Paper_t_Paper_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Paper::kDatasFieldNumber;
#endif  // !_MSC_VER

Paper::Paper()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Paper::InitAsDefaultInstance() {
}

Paper::Paper(const Paper& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Paper::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Paper::~Paper() {
  SharedDtor();
}

void Paper::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Paper::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Paper::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Paper_descriptor_;
}

const Paper& Paper::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Paper_2eproto();
  return *default_instance_;
}

Paper* Paper::default_instance_ = NULL;

Paper* Paper::New() const {
  return new Paper;
}

void Paper::Clear() {
  datas_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Paper::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .pb.Paper.t_Paper datas = 1;
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

void Paper::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .pb.Paper.t_Paper datas = 1;
  for (int i = 0; i < this->datas_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->datas(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Paper::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .pb.Paper.t_Paper datas = 1;
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

int Paper::ByteSize() const {
  int total_size = 0;

  // repeated .pb.Paper.t_Paper datas = 1;
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

void Paper::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Paper* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Paper*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Paper::MergeFrom(const Paper& from) {
  GOOGLE_CHECK_NE(&from, this);
  datas_.MergeFrom(from.datas_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Paper::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Paper::CopyFrom(const Paper& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Paper::IsInitialized() const {

  for (int i = 0; i < datas_size(); i++) {
    if (!this->datas(i).IsInitialized()) return false;
  }
  return true;
}

void Paper::Swap(Paper* other) {
  if (other != this) {
    datas_.Swap(&other->datas_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Paper::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Paper_descriptor_;
  metadata.reflection = Paper_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)