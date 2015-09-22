// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: HandBook.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "HandBook.pb.h"

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

const ::google::protobuf::Descriptor* Handbook_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Handbook_reflection_ = NULL;
const ::google::protobuf::Descriptor* Handbook_t_Handbook_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Handbook_t_Handbook_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_HandBook_2eproto() {
  protobuf_AddDesc_HandBook_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "HandBook.proto");
  GOOGLE_CHECK(file != NULL);
  Handbook_descriptor_ = file->message_type(0);
  static const int Handbook_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Handbook, datas_),
  };
  Handbook_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Handbook_descriptor_,
      Handbook::default_instance_,
      Handbook_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Handbook, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Handbook, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Handbook));
  Handbook_t_Handbook_descriptor_ = Handbook_descriptor_->nested_type(0);
  static const int Handbook_t_Handbook_offsets_[7] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Handbook_t_Handbook, tbxid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Handbook_t_Handbook, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Handbook_t_Handbook, mtype_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Handbook_t_Handbook, itemid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Handbook_t_Handbook, effectid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Handbook_t_Handbook, level_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Handbook_t_Handbook, glod_),
  };
  Handbook_t_Handbook_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Handbook_t_Handbook_descriptor_,
      Handbook_t_Handbook::default_instance_,
      Handbook_t_Handbook_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Handbook_t_Handbook, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Handbook_t_Handbook, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Handbook_t_Handbook));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_HandBook_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Handbook_descriptor_, &Handbook::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Handbook_t_Handbook_descriptor_, &Handbook_t_Handbook::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_HandBook_2eproto() {
  delete Handbook::default_instance_;
  delete Handbook_reflection_;
  delete Handbook_t_Handbook::default_instance_;
  delete Handbook_t_Handbook_reflection_;
}

void protobuf_AddDesc_HandBook_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\016HandBook.proto\022\002pb\"\251\001\n\010Handbook\022&\n\005dat"
    "as\030\001 \003(\0132\027.pb.Handbook.t_Handbook\032u\n\nt_H"
    "andbook\022\r\n\005tbxid\030\001 \002(\r\022\n\n\002id\030\002 \002(\r\022\r\n\005mt"
    "ype\030\003 \002(\r\022\016\n\006itemid\030\004 \002(\r\022\020\n\010effectId\030\005 "
    "\002(\r\022\r\n\005level\030\006 \002(\r\022\014\n\004glod\030\007 \002(\r", 192);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "HandBook.proto", &protobuf_RegisterTypes);
  Handbook::default_instance_ = new Handbook();
  Handbook_t_Handbook::default_instance_ = new Handbook_t_Handbook();
  Handbook::default_instance_->InitAsDefaultInstance();
  Handbook_t_Handbook::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_HandBook_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_HandBook_2eproto {
  StaticDescriptorInitializer_HandBook_2eproto() {
    protobuf_AddDesc_HandBook_2eproto();
  }
} static_descriptor_initializer_HandBook_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Handbook_t_Handbook::kTbxidFieldNumber;
const int Handbook_t_Handbook::kIdFieldNumber;
const int Handbook_t_Handbook::kMtypeFieldNumber;
const int Handbook_t_Handbook::kItemidFieldNumber;
const int Handbook_t_Handbook::kEffectIdFieldNumber;
const int Handbook_t_Handbook::kLevelFieldNumber;
const int Handbook_t_Handbook::kGlodFieldNumber;
#endif  // !_MSC_VER

Handbook_t_Handbook::Handbook_t_Handbook()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Handbook_t_Handbook::InitAsDefaultInstance() {
}

Handbook_t_Handbook::Handbook_t_Handbook(const Handbook_t_Handbook& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Handbook_t_Handbook::SharedCtor() {
  _cached_size_ = 0;
  tbxid_ = 0u;
  id_ = 0u;
  mtype_ = 0u;
  itemid_ = 0u;
  effectid_ = 0u;
  level_ = 0u;
  glod_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Handbook_t_Handbook::~Handbook_t_Handbook() {
  SharedDtor();
}

void Handbook_t_Handbook::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Handbook_t_Handbook::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Handbook_t_Handbook::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Handbook_t_Handbook_descriptor_;
}

const Handbook_t_Handbook& Handbook_t_Handbook::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_HandBook_2eproto();
  return *default_instance_;
}

Handbook_t_Handbook* Handbook_t_Handbook::default_instance_ = NULL;

Handbook_t_Handbook* Handbook_t_Handbook::New() const {
  return new Handbook_t_Handbook;
}

void Handbook_t_Handbook::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    tbxid_ = 0u;
    id_ = 0u;
    mtype_ = 0u;
    itemid_ = 0u;
    effectid_ = 0u;
    level_ = 0u;
    glod_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Handbook_t_Handbook::MergePartialFromCodedStream(
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
        if (input->ExpectTag(24)) goto parse_mtype;
        break;
      }

      // required uint32 mtype = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_mtype:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &mtype_)));
          set_has_mtype();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_itemid;
        break;
      }

      // required uint32 itemid = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_itemid:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &itemid_)));
          set_has_itemid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_effectId;
        break;
      }

      // required uint32 effectId = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_effectId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &effectid_)));
          set_has_effectid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_level;
        break;
      }

      // required uint32 level = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_level:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &level_)));
          set_has_level();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_glod;
        break;
      }

      // required uint32 glod = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_glod:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &glod_)));
          set_has_glod();
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

void Handbook_t_Handbook::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 tbxid = 1;
  if (has_tbxid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->tbxid(), output);
  }

  // required uint32 id = 2;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->id(), output);
  }

  // required uint32 mtype = 3;
  if (has_mtype()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->mtype(), output);
  }

  // required uint32 itemid = 4;
  if (has_itemid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->itemid(), output);
  }

  // required uint32 effectId = 5;
  if (has_effectid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->effectid(), output);
  }

  // required uint32 level = 6;
  if (has_level()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->level(), output);
  }

  // required uint32 glod = 7;
  if (has_glod()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(7, this->glod(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Handbook_t_Handbook::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 tbxid = 1;
  if (has_tbxid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->tbxid(), target);
  }

  // required uint32 id = 2;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->id(), target);
  }

  // required uint32 mtype = 3;
  if (has_mtype()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->mtype(), target);
  }

  // required uint32 itemid = 4;
  if (has_itemid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->itemid(), target);
  }

  // required uint32 effectId = 5;
  if (has_effectid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->effectid(), target);
  }

  // required uint32 level = 6;
  if (has_level()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->level(), target);
  }

  // required uint32 glod = 7;
  if (has_glod()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(7, this->glod(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Handbook_t_Handbook::ByteSize() const {
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

    // required uint32 mtype = 3;
    if (has_mtype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->mtype());
    }

    // required uint32 itemid = 4;
    if (has_itemid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->itemid());
    }

    // required uint32 effectId = 5;
    if (has_effectid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->effectid());
    }

    // required uint32 level = 6;
    if (has_level()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->level());
    }

    // required uint32 glod = 7;
    if (has_glod()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->glod());
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

void Handbook_t_Handbook::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Handbook_t_Handbook* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Handbook_t_Handbook*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Handbook_t_Handbook::MergeFrom(const Handbook_t_Handbook& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_tbxid()) {
      set_tbxid(from.tbxid());
    }
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_mtype()) {
      set_mtype(from.mtype());
    }
    if (from.has_itemid()) {
      set_itemid(from.itemid());
    }
    if (from.has_effectid()) {
      set_effectid(from.effectid());
    }
    if (from.has_level()) {
      set_level(from.level());
    }
    if (from.has_glod()) {
      set_glod(from.glod());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Handbook_t_Handbook::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Handbook_t_Handbook::CopyFrom(const Handbook_t_Handbook& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Handbook_t_Handbook::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000007f) != 0x0000007f) return false;

  return true;
}

void Handbook_t_Handbook::Swap(Handbook_t_Handbook* other) {
  if (other != this) {
    std::swap(tbxid_, other->tbxid_);
    std::swap(id_, other->id_);
    std::swap(mtype_, other->mtype_);
    std::swap(itemid_, other->itemid_);
    std::swap(effectid_, other->effectid_);
    std::swap(level_, other->level_);
    std::swap(glod_, other->glod_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Handbook_t_Handbook::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Handbook_t_Handbook_descriptor_;
  metadata.reflection = Handbook_t_Handbook_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Handbook::kDatasFieldNumber;
#endif  // !_MSC_VER

Handbook::Handbook()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Handbook::InitAsDefaultInstance() {
}

Handbook::Handbook(const Handbook& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Handbook::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Handbook::~Handbook() {
  SharedDtor();
}

void Handbook::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Handbook::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Handbook::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Handbook_descriptor_;
}

const Handbook& Handbook::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_HandBook_2eproto();
  return *default_instance_;
}

Handbook* Handbook::default_instance_ = NULL;

Handbook* Handbook::New() const {
  return new Handbook;
}

void Handbook::Clear() {
  datas_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Handbook::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .pb.Handbook.t_Handbook datas = 1;
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

void Handbook::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .pb.Handbook.t_Handbook datas = 1;
  for (int i = 0; i < this->datas_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->datas(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Handbook::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .pb.Handbook.t_Handbook datas = 1;
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

int Handbook::ByteSize() const {
  int total_size = 0;

  // repeated .pb.Handbook.t_Handbook datas = 1;
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

void Handbook::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Handbook* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Handbook*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Handbook::MergeFrom(const Handbook& from) {
  GOOGLE_CHECK_NE(&from, this);
  datas_.MergeFrom(from.datas_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Handbook::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Handbook::CopyFrom(const Handbook& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Handbook::IsInitialized() const {

  for (int i = 0; i < datas_size(); i++) {
    if (!this->datas(i).IsInitialized()) return false;
  }
  return true;
}

void Handbook::Swap(Handbook* other) {
  if (other != this) {
    datas_.Swap(&other->datas_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Handbook::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Handbook_descriptor_;
  metadata.reflection = Handbook_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)
