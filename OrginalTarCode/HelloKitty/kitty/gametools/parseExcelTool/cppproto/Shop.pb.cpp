// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Shop.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Shop.pb.h"

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

const ::google::protobuf::Descriptor* Shop_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Shop_reflection_ = NULL;
const ::google::protobuf::Descriptor* Shop_t_Shop_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Shop_t_Shop_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Shop_2eproto() {
  protobuf_AddDesc_Shop_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Shop.proto");
  GOOGLE_CHECK(file != NULL);
  Shop_descriptor_ = file->message_type(0);
  static const int Shop_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Shop, datas_),
  };
  Shop_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Shop_descriptor_,
      Shop::default_instance_,
      Shop_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Shop, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Shop, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Shop));
  Shop_t_Shop_descriptor_ = Shop_descriptor_->nested_type(0);
  static const int Shop_t_Shop_offsets_[9] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Shop_t_Shop, tbxid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Shop_t_Shop, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Shop_t_Shop, mtype_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Shop_t_Shop, itemid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Shop_t_Shop, stype_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Shop_t_Shop, ctype_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Shop_t_Shop, price_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Shop_t_Shop, disprice_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Shop_t_Shop, max_),
  };
  Shop_t_Shop_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Shop_t_Shop_descriptor_,
      Shop_t_Shop::default_instance_,
      Shop_t_Shop_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Shop_t_Shop, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Shop_t_Shop, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Shop_t_Shop));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Shop_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Shop_descriptor_, &Shop::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Shop_t_Shop_descriptor_, &Shop_t_Shop::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Shop_2eproto() {
  delete Shop::default_instance_;
  delete Shop_reflection_;
  delete Shop_t_Shop::default_instance_;
  delete Shop_t_Shop_reflection_;
}

void protobuf_AddDesc_Shop_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\nShop.proto\022\002pb\"\267\001\n\004Shop\022\036\n\005datas\030\001 \003(\013"
    "2\017.pb.Shop.t_Shop\032\216\001\n\006t_Shop\022\r\n\005tbxid\030\001 "
    "\002(\r\022\n\n\002id\030\002 \002(\r\022\r\n\005mtype\030\003 \002(\r\022\016\n\006itemid"
    "\030\004 \002(\r\022\r\n\005stype\030\005 \002(\r\022\r\n\005ctype\030\006 \002(\r\022\r\n\005"
    "price\030\007 \002(\r\022\020\n\010disPrice\030\010 \002(\r\022\013\n\003max\030\t \002"
    "(\r", 202);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Shop.proto", &protobuf_RegisterTypes);
  Shop::default_instance_ = new Shop();
  Shop_t_Shop::default_instance_ = new Shop_t_Shop();
  Shop::default_instance_->InitAsDefaultInstance();
  Shop_t_Shop::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Shop_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Shop_2eproto {
  StaticDescriptorInitializer_Shop_2eproto() {
    protobuf_AddDesc_Shop_2eproto();
  }
} static_descriptor_initializer_Shop_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Shop_t_Shop::kTbxidFieldNumber;
const int Shop_t_Shop::kIdFieldNumber;
const int Shop_t_Shop::kMtypeFieldNumber;
const int Shop_t_Shop::kItemidFieldNumber;
const int Shop_t_Shop::kStypeFieldNumber;
const int Shop_t_Shop::kCtypeFieldNumber;
const int Shop_t_Shop::kPriceFieldNumber;
const int Shop_t_Shop::kDisPriceFieldNumber;
const int Shop_t_Shop::kMaxFieldNumber;
#endif  // !_MSC_VER

Shop_t_Shop::Shop_t_Shop()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Shop_t_Shop::InitAsDefaultInstance() {
}

Shop_t_Shop::Shop_t_Shop(const Shop_t_Shop& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Shop_t_Shop::SharedCtor() {
  _cached_size_ = 0;
  tbxid_ = 0u;
  id_ = 0u;
  mtype_ = 0u;
  itemid_ = 0u;
  stype_ = 0u;
  ctype_ = 0u;
  price_ = 0u;
  disprice_ = 0u;
  max_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Shop_t_Shop::~Shop_t_Shop() {
  SharedDtor();
}

void Shop_t_Shop::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Shop_t_Shop::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Shop_t_Shop::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Shop_t_Shop_descriptor_;
}

const Shop_t_Shop& Shop_t_Shop::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Shop_2eproto();
  return *default_instance_;
}

Shop_t_Shop* Shop_t_Shop::default_instance_ = NULL;

Shop_t_Shop* Shop_t_Shop::New() const {
  return new Shop_t_Shop;
}

void Shop_t_Shop::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    tbxid_ = 0u;
    id_ = 0u;
    mtype_ = 0u;
    itemid_ = 0u;
    stype_ = 0u;
    ctype_ = 0u;
    price_ = 0u;
    disprice_ = 0u;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    max_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Shop_t_Shop::MergePartialFromCodedStream(
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
        if (input->ExpectTag(40)) goto parse_stype;
        break;
      }

      // required uint32 stype = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_stype:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &stype_)));
          set_has_stype();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_ctype;
        break;
      }

      // required uint32 ctype = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_ctype:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &ctype_)));
          set_has_ctype();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_price;
        break;
      }

      // required uint32 price = 7;
      case 7: {
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
        if (input->ExpectTag(64)) goto parse_disPrice;
        break;
      }

      // required uint32 disPrice = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_disPrice:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &disprice_)));
          set_has_disprice();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(72)) goto parse_max;
        break;
      }

      // required uint32 max = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_max:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &max_)));
          set_has_max();
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

void Shop_t_Shop::SerializeWithCachedSizes(
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

  // required uint32 stype = 5;
  if (has_stype()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->stype(), output);
  }

  // required uint32 ctype = 6;
  if (has_ctype()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->ctype(), output);
  }

  // required uint32 price = 7;
  if (has_price()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(7, this->price(), output);
  }

  // required uint32 disPrice = 8;
  if (has_disprice()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(8, this->disprice(), output);
  }

  // required uint32 max = 9;
  if (has_max()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(9, this->max(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Shop_t_Shop::SerializeWithCachedSizesToArray(
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

  // required uint32 stype = 5;
  if (has_stype()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->stype(), target);
  }

  // required uint32 ctype = 6;
  if (has_ctype()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->ctype(), target);
  }

  // required uint32 price = 7;
  if (has_price()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(7, this->price(), target);
  }

  // required uint32 disPrice = 8;
  if (has_disprice()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(8, this->disprice(), target);
  }

  // required uint32 max = 9;
  if (has_max()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(9, this->max(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Shop_t_Shop::ByteSize() const {
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

    // required uint32 stype = 5;
    if (has_stype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->stype());
    }

    // required uint32 ctype = 6;
    if (has_ctype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->ctype());
    }

    // required uint32 price = 7;
    if (has_price()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->price());
    }

    // required uint32 disPrice = 8;
    if (has_disprice()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->disprice());
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // required uint32 max = 9;
    if (has_max()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->max());
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

void Shop_t_Shop::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Shop_t_Shop* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Shop_t_Shop*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Shop_t_Shop::MergeFrom(const Shop_t_Shop& from) {
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
    if (from.has_stype()) {
      set_stype(from.stype());
    }
    if (from.has_ctype()) {
      set_ctype(from.ctype());
    }
    if (from.has_price()) {
      set_price(from.price());
    }
    if (from.has_disprice()) {
      set_disprice(from.disprice());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_max()) {
      set_max(from.max());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Shop_t_Shop::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Shop_t_Shop::CopyFrom(const Shop_t_Shop& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Shop_t_Shop::IsInitialized() const {
  if ((_has_bits_[0] & 0x000001ff) != 0x000001ff) return false;

  return true;
}

void Shop_t_Shop::Swap(Shop_t_Shop* other) {
  if (other != this) {
    std::swap(tbxid_, other->tbxid_);
    std::swap(id_, other->id_);
    std::swap(mtype_, other->mtype_);
    std::swap(itemid_, other->itemid_);
    std::swap(stype_, other->stype_);
    std::swap(ctype_, other->ctype_);
    std::swap(price_, other->price_);
    std::swap(disprice_, other->disprice_);
    std::swap(max_, other->max_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Shop_t_Shop::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Shop_t_Shop_descriptor_;
  metadata.reflection = Shop_t_Shop_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Shop::kDatasFieldNumber;
#endif  // !_MSC_VER

Shop::Shop()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Shop::InitAsDefaultInstance() {
}

Shop::Shop(const Shop& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Shop::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Shop::~Shop() {
  SharedDtor();
}

void Shop::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Shop::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Shop::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Shop_descriptor_;
}

const Shop& Shop::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Shop_2eproto();
  return *default_instance_;
}

Shop* Shop::default_instance_ = NULL;

Shop* Shop::New() const {
  return new Shop;
}

void Shop::Clear() {
  datas_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Shop::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .pb.Shop.t_Shop datas = 1;
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

void Shop::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .pb.Shop.t_Shop datas = 1;
  for (int i = 0; i < this->datas_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->datas(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Shop::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .pb.Shop.t_Shop datas = 1;
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

int Shop::ByteSize() const {
  int total_size = 0;

  // repeated .pb.Shop.t_Shop datas = 1;
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

void Shop::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Shop* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Shop*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Shop::MergeFrom(const Shop& from) {
  GOOGLE_CHECK_NE(&from, this);
  datas_.MergeFrom(from.datas_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Shop::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Shop::CopyFrom(const Shop& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Shop::IsInitialized() const {

  for (int i = 0; i < datas_size(); i++) {
    if (!this->datas(i).IsInitialized()) return false;
  }
  return true;
}

void Shop::Swap(Shop* other) {
  if (other != this) {
    datas_.Swap(&other->datas_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Shop::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Shop_descriptor_;
  metadata.reflection = Shop_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)
