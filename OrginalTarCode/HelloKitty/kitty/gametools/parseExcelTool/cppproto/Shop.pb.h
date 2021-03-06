// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Shop.proto

#ifndef PROTOBUF_Shop_2eproto__INCLUDED
#define PROTOBUF_Shop_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace pb {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Shop_2eproto();
void protobuf_AssignDesc_Shop_2eproto();
void protobuf_ShutdownFile_Shop_2eproto();

class Shop;
class Shop_t_Shop;

// ===================================================================

class Shop_t_Shop : public ::google::protobuf::Message {
 public:
  Shop_t_Shop();
  virtual ~Shop_t_Shop();

  Shop_t_Shop(const Shop_t_Shop& from);

  inline Shop_t_Shop& operator=(const Shop_t_Shop& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Shop_t_Shop& default_instance();

  void Swap(Shop_t_Shop* other);

  // implements Message ----------------------------------------------

  Shop_t_Shop* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Shop_t_Shop& from);
  void MergeFrom(const Shop_t_Shop& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required uint32 tbxid = 1;
  inline bool has_tbxid() const;
  inline void clear_tbxid();
  static const int kTbxidFieldNumber = 1;
  inline ::google::protobuf::uint32 tbxid() const;
  inline void set_tbxid(::google::protobuf::uint32 value);

  // required uint32 id = 2;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 2;
  inline ::google::protobuf::uint32 id() const;
  inline void set_id(::google::protobuf::uint32 value);

  // required uint32 mtype = 3;
  inline bool has_mtype() const;
  inline void clear_mtype();
  static const int kMtypeFieldNumber = 3;
  inline ::google::protobuf::uint32 mtype() const;
  inline void set_mtype(::google::protobuf::uint32 value);

  // required uint32 itemid = 4;
  inline bool has_itemid() const;
  inline void clear_itemid();
  static const int kItemidFieldNumber = 4;
  inline ::google::protobuf::uint32 itemid() const;
  inline void set_itemid(::google::protobuf::uint32 value);

  // required uint32 stype = 5;
  inline bool has_stype() const;
  inline void clear_stype();
  static const int kStypeFieldNumber = 5;
  inline ::google::protobuf::uint32 stype() const;
  inline void set_stype(::google::protobuf::uint32 value);

  // required uint32 ctype = 6;
  inline bool has_ctype() const;
  inline void clear_ctype();
  static const int kCtypeFieldNumber = 6;
  inline ::google::protobuf::uint32 ctype() const;
  inline void set_ctype(::google::protobuf::uint32 value);

  // required uint32 price = 7;
  inline bool has_price() const;
  inline void clear_price();
  static const int kPriceFieldNumber = 7;
  inline ::google::protobuf::uint32 price() const;
  inline void set_price(::google::protobuf::uint32 value);

  // required uint32 disPrice = 8;
  inline bool has_disprice() const;
  inline void clear_disprice();
  static const int kDisPriceFieldNumber = 8;
  inline ::google::protobuf::uint32 disprice() const;
  inline void set_disprice(::google::protobuf::uint32 value);

  // required uint32 max = 9;
  inline bool has_max() const;
  inline void clear_max();
  static const int kMaxFieldNumber = 9;
  inline ::google::protobuf::uint32 max() const;
  inline void set_max(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:pb.Shop.t_Shop)
 private:
  inline void set_has_tbxid();
  inline void clear_has_tbxid();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_mtype();
  inline void clear_has_mtype();
  inline void set_has_itemid();
  inline void clear_has_itemid();
  inline void set_has_stype();
  inline void clear_has_stype();
  inline void set_has_ctype();
  inline void clear_has_ctype();
  inline void set_has_price();
  inline void clear_has_price();
  inline void set_has_disprice();
  inline void clear_has_disprice();
  inline void set_has_max();
  inline void clear_has_max();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 tbxid_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 mtype_;
  ::google::protobuf::uint32 itemid_;
  ::google::protobuf::uint32 stype_;
  ::google::protobuf::uint32 ctype_;
  ::google::protobuf::uint32 price_;
  ::google::protobuf::uint32 disprice_;
  ::google::protobuf::uint32 max_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(9 + 31) / 32];

  friend void  protobuf_AddDesc_Shop_2eproto();
  friend void protobuf_AssignDesc_Shop_2eproto();
  friend void protobuf_ShutdownFile_Shop_2eproto();

  void InitAsDefaultInstance();
  static Shop_t_Shop* default_instance_;
};
// -------------------------------------------------------------------

class Shop : public ::google::protobuf::Message {
 public:
  Shop();
  virtual ~Shop();

  Shop(const Shop& from);

  inline Shop& operator=(const Shop& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Shop& default_instance();

  void Swap(Shop* other);

  // implements Message ----------------------------------------------

  Shop* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Shop& from);
  void MergeFrom(const Shop& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef Shop_t_Shop t_Shop;

  // accessors -------------------------------------------------------

  // repeated .pb.Shop.t_Shop datas = 1;
  inline int datas_size() const;
  inline void clear_datas();
  static const int kDatasFieldNumber = 1;
  inline const ::pb::Shop_t_Shop& datas(int index) const;
  inline ::pb::Shop_t_Shop* mutable_datas(int index);
  inline ::pb::Shop_t_Shop* add_datas();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::Shop_t_Shop >&
      datas() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::Shop_t_Shop >*
      mutable_datas();

  // @@protoc_insertion_point(class_scope:pb.Shop)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::pb::Shop_t_Shop > datas_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_Shop_2eproto();
  friend void protobuf_AssignDesc_Shop_2eproto();
  friend void protobuf_ShutdownFile_Shop_2eproto();

  void InitAsDefaultInstance();
  static Shop* default_instance_;
};
// ===================================================================


// ===================================================================

// Shop_t_Shop

// required uint32 tbxid = 1;
inline bool Shop_t_Shop::has_tbxid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Shop_t_Shop::set_has_tbxid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Shop_t_Shop::clear_has_tbxid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Shop_t_Shop::clear_tbxid() {
  tbxid_ = 0u;
  clear_has_tbxid();
}
inline ::google::protobuf::uint32 Shop_t_Shop::tbxid() const {
  return tbxid_;
}
inline void Shop_t_Shop::set_tbxid(::google::protobuf::uint32 value) {
  set_has_tbxid();
  tbxid_ = value;
}

// required uint32 id = 2;
inline bool Shop_t_Shop::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Shop_t_Shop::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Shop_t_Shop::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Shop_t_Shop::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 Shop_t_Shop::id() const {
  return id_;
}
inline void Shop_t_Shop::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required uint32 mtype = 3;
inline bool Shop_t_Shop::has_mtype() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Shop_t_Shop::set_has_mtype() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Shop_t_Shop::clear_has_mtype() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Shop_t_Shop::clear_mtype() {
  mtype_ = 0u;
  clear_has_mtype();
}
inline ::google::protobuf::uint32 Shop_t_Shop::mtype() const {
  return mtype_;
}
inline void Shop_t_Shop::set_mtype(::google::protobuf::uint32 value) {
  set_has_mtype();
  mtype_ = value;
}

// required uint32 itemid = 4;
inline bool Shop_t_Shop::has_itemid() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Shop_t_Shop::set_has_itemid() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Shop_t_Shop::clear_has_itemid() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Shop_t_Shop::clear_itemid() {
  itemid_ = 0u;
  clear_has_itemid();
}
inline ::google::protobuf::uint32 Shop_t_Shop::itemid() const {
  return itemid_;
}
inline void Shop_t_Shop::set_itemid(::google::protobuf::uint32 value) {
  set_has_itemid();
  itemid_ = value;
}

// required uint32 stype = 5;
inline bool Shop_t_Shop::has_stype() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Shop_t_Shop::set_has_stype() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Shop_t_Shop::clear_has_stype() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Shop_t_Shop::clear_stype() {
  stype_ = 0u;
  clear_has_stype();
}
inline ::google::protobuf::uint32 Shop_t_Shop::stype() const {
  return stype_;
}
inline void Shop_t_Shop::set_stype(::google::protobuf::uint32 value) {
  set_has_stype();
  stype_ = value;
}

// required uint32 ctype = 6;
inline bool Shop_t_Shop::has_ctype() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Shop_t_Shop::set_has_ctype() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Shop_t_Shop::clear_has_ctype() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Shop_t_Shop::clear_ctype() {
  ctype_ = 0u;
  clear_has_ctype();
}
inline ::google::protobuf::uint32 Shop_t_Shop::ctype() const {
  return ctype_;
}
inline void Shop_t_Shop::set_ctype(::google::protobuf::uint32 value) {
  set_has_ctype();
  ctype_ = value;
}

// required uint32 price = 7;
inline bool Shop_t_Shop::has_price() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void Shop_t_Shop::set_has_price() {
  _has_bits_[0] |= 0x00000040u;
}
inline void Shop_t_Shop::clear_has_price() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void Shop_t_Shop::clear_price() {
  price_ = 0u;
  clear_has_price();
}
inline ::google::protobuf::uint32 Shop_t_Shop::price() const {
  return price_;
}
inline void Shop_t_Shop::set_price(::google::protobuf::uint32 value) {
  set_has_price();
  price_ = value;
}

// required uint32 disPrice = 8;
inline bool Shop_t_Shop::has_disprice() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void Shop_t_Shop::set_has_disprice() {
  _has_bits_[0] |= 0x00000080u;
}
inline void Shop_t_Shop::clear_has_disprice() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void Shop_t_Shop::clear_disprice() {
  disprice_ = 0u;
  clear_has_disprice();
}
inline ::google::protobuf::uint32 Shop_t_Shop::disprice() const {
  return disprice_;
}
inline void Shop_t_Shop::set_disprice(::google::protobuf::uint32 value) {
  set_has_disprice();
  disprice_ = value;
}

// required uint32 max = 9;
inline bool Shop_t_Shop::has_max() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void Shop_t_Shop::set_has_max() {
  _has_bits_[0] |= 0x00000100u;
}
inline void Shop_t_Shop::clear_has_max() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void Shop_t_Shop::clear_max() {
  max_ = 0u;
  clear_has_max();
}
inline ::google::protobuf::uint32 Shop_t_Shop::max() const {
  return max_;
}
inline void Shop_t_Shop::set_max(::google::protobuf::uint32 value) {
  set_has_max();
  max_ = value;
}

// -------------------------------------------------------------------

// Shop

// repeated .pb.Shop.t_Shop datas = 1;
inline int Shop::datas_size() const {
  return datas_.size();
}
inline void Shop::clear_datas() {
  datas_.Clear();
}
inline const ::pb::Shop_t_Shop& Shop::datas(int index) const {
  return datas_.Get(index);
}
inline ::pb::Shop_t_Shop* Shop::mutable_datas(int index) {
  return datas_.Mutable(index);
}
inline ::pb::Shop_t_Shop* Shop::add_datas() {
  return datas_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::Shop_t_Shop >&
Shop::datas() const {
  return datas_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::Shop_t_Shop >*
Shop::mutable_datas() {
  return &datas_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Shop_2eproto__INCLUDED
