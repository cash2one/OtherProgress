// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: serialize.proto

#ifndef PROTOBUF_serialize_2eproto__INCLUDED
#define PROTOBUF_serialize_2eproto__INCLUDED

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
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include "item.pb.h"
#include "trade.pb.h"
// @@protoc_insertion_point(includes)

namespace HelloKittyMsgData {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_serialize_2eproto();
void protobuf_AssignDesc_serialize_2eproto();
void protobuf_ShutdownFile_serialize_2eproto();

class PbCounter;
class Serialize;
class MsgSaleCell;

enum CounterResetType {
  Reset_No = 0,
  Reset_Day = 1,
  Reset_SixHour = 2,
  Reset_Week = 3,
  Reset_Month = 4
};
bool CounterResetType_IsValid(int value);
const CounterResetType CounterResetType_MIN = Reset_No;
const CounterResetType CounterResetType_MAX = Reset_Month;
const int CounterResetType_ARRAYSIZE = CounterResetType_MAX + 1;

const ::google::protobuf::EnumDescriptor* CounterResetType_descriptor();
inline const ::std::string& CounterResetType_Name(CounterResetType value) {
  return ::google::protobuf::internal::NameOfEnum(
    CounterResetType_descriptor(), value);
}
inline bool CounterResetType_Parse(
    const ::std::string& name, CounterResetType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<CounterResetType>(
    CounterResetType_descriptor(), name, value);
}
// ===================================================================

class PbCounter : public ::google::protobuf::Message {
 public:
  PbCounter();
  virtual ~PbCounter();

  PbCounter(const PbCounter& from);

  inline PbCounter& operator=(const PbCounter& from) {
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
  static const PbCounter& default_instance();

  void Swap(PbCounter* other);

  // implements Message ----------------------------------------------

  PbCounter* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PbCounter& from);
  void MergeFrom(const PbCounter& from);
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

  // optional uint32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::uint32 id() const;
  inline void set_id(::google::protobuf::uint32 value);

  // optional .HelloKittyMsgData.CounterResetType type = 2;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 2;
  inline ::HelloKittyMsgData::CounterResetType type() const;
  inline void set_type(::HelloKittyMsgData::CounterResetType value);

  // optional uint32 lastTime = 3;
  inline bool has_lasttime() const;
  inline void clear_lasttime();
  static const int kLastTimeFieldNumber = 3;
  inline ::google::protobuf::uint32 lasttime() const;
  inline void set_lasttime(::google::protobuf::uint32 value);

  // optional uint32 count = 4;
  inline bool has_count() const;
  inline void clear_count();
  static const int kCountFieldNumber = 4;
  inline ::google::protobuf::uint32 count() const;
  inline void set_count(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.PbCounter)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_lasttime();
  inline void clear_has_lasttime();
  inline void set_has_count();
  inline void clear_has_count();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 id_;
  int type_;
  ::google::protobuf::uint32 lasttime_;
  ::google::protobuf::uint32 count_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];

  friend void  protobuf_AddDesc_serialize_2eproto();
  friend void protobuf_AssignDesc_serialize_2eproto();
  friend void protobuf_ShutdownFile_serialize_2eproto();

  void InitAsDefaultInstance();
  static PbCounter* default_instance_;
};
// -------------------------------------------------------------------

class Serialize : public ::google::protobuf::Message {
 public:
  Serialize();
  virtual ~Serialize();

  Serialize(const Serialize& from);

  inline Serialize& operator=(const Serialize& from) {
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
  static const Serialize& default_instance();

  void Swap(Serialize* other);

  // implements Message ----------------------------------------------

  Serialize* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Serialize& from);
  void MergeFrom(const Serialize& from);
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

  // repeated .HelloKittyMsgData.PbCounter pb_counters = 1;
  inline int pb_counters_size() const;
  inline void clear_pb_counters();
  static const int kPbCountersFieldNumber = 1;
  inline const ::HelloKittyMsgData::PbCounter& pb_counters(int index) const;
  inline ::HelloKittyMsgData::PbCounter* mutable_pb_counters(int index);
  inline ::HelloKittyMsgData::PbCounter* add_pb_counters();
  inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbCounter >&
      pb_counters() const;
  inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbCounter >*
      mutable_pb_counters();

  // repeated .HelloKittyMsgData.PbStoreItem store_items = 2;
  inline int store_items_size() const;
  inline void clear_store_items();
  static const int kStoreItemsFieldNumber = 2;
  inline const ::HelloKittyMsgData::PbStoreItem& store_items(int index) const;
  inline ::HelloKittyMsgData::PbStoreItem* mutable_store_items(int index);
  inline ::HelloKittyMsgData::PbStoreItem* add_store_items();
  inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbStoreItem >&
      store_items() const;
  inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbStoreItem >*
      mutable_store_items();

  // optional .HelloKittyMsgData.PbSaleBooth saleBooth = 3;
  inline bool has_salebooth() const;
  inline void clear_salebooth();
  static const int kSaleBoothFieldNumber = 3;
  inline const ::HelloKittyMsgData::PbSaleBooth& salebooth() const;
  inline ::HelloKittyMsgData::PbSaleBooth* mutable_salebooth();
  inline ::HelloKittyMsgData::PbSaleBooth* release_salebooth();
  inline void set_allocated_salebooth(::HelloKittyMsgData::PbSaleBooth* salebooth);

  // repeated .HelloKittyMsgData.Factor factor = 4;
  inline int factor_size() const;
  inline void clear_factor();
  static const int kFactorFieldNumber = 4;
  inline const ::HelloKittyMsgData::Factor& factor(int index) const;
  inline ::HelloKittyMsgData::Factor* mutable_factor(int index);
  inline ::HelloKittyMsgData::Factor* add_factor();
  inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::Factor >&
      factor() const;
  inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::Factor >*
      mutable_factor();

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.Serialize)
 private:
  inline void set_has_salebooth();
  inline void clear_has_salebooth();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbCounter > pb_counters_;
  ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbStoreItem > store_items_;
  ::HelloKittyMsgData::PbSaleBooth* salebooth_;
  ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::Factor > factor_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];

  friend void  protobuf_AddDesc_serialize_2eproto();
  friend void protobuf_AssignDesc_serialize_2eproto();
  friend void protobuf_ShutdownFile_serialize_2eproto();

  void InitAsDefaultInstance();
  static Serialize* default_instance_;
};
// -------------------------------------------------------------------

class MsgSaleCell : public ::google::protobuf::Message {
 public:
  MsgSaleCell();
  virtual ~MsgSaleCell();

  MsgSaleCell(const MsgSaleCell& from);

  inline MsgSaleCell& operator=(const MsgSaleCell& from) {
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
  static const MsgSaleCell& default_instance();

  void Swap(MsgSaleCell* other);

  // implements Message ----------------------------------------------

  MsgSaleCell* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MsgSaleCell& from);
  void MergeFrom(const MsgSaleCell& from);
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

  // repeated .HelloKittyMsgData.PbCounter pb_counters = 1;
  inline int pb_counters_size() const;
  inline void clear_pb_counters();
  static const int kPbCountersFieldNumber = 1;
  inline const ::HelloKittyMsgData::PbCounter& pb_counters(int index) const;
  inline ::HelloKittyMsgData::PbCounter* mutable_pb_counters(int index);
  inline ::HelloKittyMsgData::PbCounter* add_pb_counters();
  inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbCounter >&
      pb_counters() const;
  inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbCounter >*
      mutable_pb_counters();

  // repeated .HelloKittyMsgData.PbStoreItem store_items = 2;
  inline int store_items_size() const;
  inline void clear_store_items();
  static const int kStoreItemsFieldNumber = 2;
  inline const ::HelloKittyMsgData::PbStoreItem& store_items(int index) const;
  inline ::HelloKittyMsgData::PbStoreItem* mutable_store_items(int index);
  inline ::HelloKittyMsgData::PbStoreItem* add_store_items();
  inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbStoreItem >&
      store_items() const;
  inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbStoreItem >*
      mutable_store_items();

  // optional .HelloKittyMsgData.PbSaleBooth saleBooth = 3;
  inline bool has_salebooth() const;
  inline void clear_salebooth();
  static const int kSaleBoothFieldNumber = 3;
  inline const ::HelloKittyMsgData::PbSaleBooth& salebooth() const;
  inline ::HelloKittyMsgData::PbSaleBooth* mutable_salebooth();
  inline ::HelloKittyMsgData::PbSaleBooth* release_salebooth();
  inline void set_allocated_salebooth(::HelloKittyMsgData::PbSaleBooth* salebooth);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.MsgSaleCell)
 private:
  inline void set_has_salebooth();
  inline void clear_has_salebooth();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbCounter > pb_counters_;
  ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbStoreItem > store_items_;
  ::HelloKittyMsgData::PbSaleBooth* salebooth_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_serialize_2eproto();
  friend void protobuf_AssignDesc_serialize_2eproto();
  friend void protobuf_ShutdownFile_serialize_2eproto();

  void InitAsDefaultInstance();
  static MsgSaleCell* default_instance_;
};
// ===================================================================


// ===================================================================

// PbCounter

// optional uint32 id = 1;
inline bool PbCounter::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PbCounter::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PbCounter::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PbCounter::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 PbCounter::id() const {
  return id_;
}
inline void PbCounter::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// optional .HelloKittyMsgData.CounterResetType type = 2;
inline bool PbCounter::has_type() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PbCounter::set_has_type() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PbCounter::clear_has_type() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PbCounter::clear_type() {
  type_ = 0;
  clear_has_type();
}
inline ::HelloKittyMsgData::CounterResetType PbCounter::type() const {
  return static_cast< ::HelloKittyMsgData::CounterResetType >(type_);
}
inline void PbCounter::set_type(::HelloKittyMsgData::CounterResetType value) {
  assert(::HelloKittyMsgData::CounterResetType_IsValid(value));
  set_has_type();
  type_ = value;
}

// optional uint32 lastTime = 3;
inline bool PbCounter::has_lasttime() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void PbCounter::set_has_lasttime() {
  _has_bits_[0] |= 0x00000004u;
}
inline void PbCounter::clear_has_lasttime() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void PbCounter::clear_lasttime() {
  lasttime_ = 0u;
  clear_has_lasttime();
}
inline ::google::protobuf::uint32 PbCounter::lasttime() const {
  return lasttime_;
}
inline void PbCounter::set_lasttime(::google::protobuf::uint32 value) {
  set_has_lasttime();
  lasttime_ = value;
}

// optional uint32 count = 4;
inline bool PbCounter::has_count() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void PbCounter::set_has_count() {
  _has_bits_[0] |= 0x00000008u;
}
inline void PbCounter::clear_has_count() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void PbCounter::clear_count() {
  count_ = 0u;
  clear_has_count();
}
inline ::google::protobuf::uint32 PbCounter::count() const {
  return count_;
}
inline void PbCounter::set_count(::google::protobuf::uint32 value) {
  set_has_count();
  count_ = value;
}

// -------------------------------------------------------------------

// Serialize

// repeated .HelloKittyMsgData.PbCounter pb_counters = 1;
inline int Serialize::pb_counters_size() const {
  return pb_counters_.size();
}
inline void Serialize::clear_pb_counters() {
  pb_counters_.Clear();
}
inline const ::HelloKittyMsgData::PbCounter& Serialize::pb_counters(int index) const {
  return pb_counters_.Get(index);
}
inline ::HelloKittyMsgData::PbCounter* Serialize::mutable_pb_counters(int index) {
  return pb_counters_.Mutable(index);
}
inline ::HelloKittyMsgData::PbCounter* Serialize::add_pb_counters() {
  return pb_counters_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbCounter >&
Serialize::pb_counters() const {
  return pb_counters_;
}
inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbCounter >*
Serialize::mutable_pb_counters() {
  return &pb_counters_;
}

// repeated .HelloKittyMsgData.PbStoreItem store_items = 2;
inline int Serialize::store_items_size() const {
  return store_items_.size();
}
inline void Serialize::clear_store_items() {
  store_items_.Clear();
}
inline const ::HelloKittyMsgData::PbStoreItem& Serialize::store_items(int index) const {
  return store_items_.Get(index);
}
inline ::HelloKittyMsgData::PbStoreItem* Serialize::mutable_store_items(int index) {
  return store_items_.Mutable(index);
}
inline ::HelloKittyMsgData::PbStoreItem* Serialize::add_store_items() {
  return store_items_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbStoreItem >&
Serialize::store_items() const {
  return store_items_;
}
inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbStoreItem >*
Serialize::mutable_store_items() {
  return &store_items_;
}

// optional .HelloKittyMsgData.PbSaleBooth saleBooth = 3;
inline bool Serialize::has_salebooth() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Serialize::set_has_salebooth() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Serialize::clear_has_salebooth() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Serialize::clear_salebooth() {
  if (salebooth_ != NULL) salebooth_->::HelloKittyMsgData::PbSaleBooth::Clear();
  clear_has_salebooth();
}
inline const ::HelloKittyMsgData::PbSaleBooth& Serialize::salebooth() const {
  return salebooth_ != NULL ? *salebooth_ : *default_instance_->salebooth_;
}
inline ::HelloKittyMsgData::PbSaleBooth* Serialize::mutable_salebooth() {
  set_has_salebooth();
  if (salebooth_ == NULL) salebooth_ = new ::HelloKittyMsgData::PbSaleBooth;
  return salebooth_;
}
inline ::HelloKittyMsgData::PbSaleBooth* Serialize::release_salebooth() {
  clear_has_salebooth();
  ::HelloKittyMsgData::PbSaleBooth* temp = salebooth_;
  salebooth_ = NULL;
  return temp;
}
inline void Serialize::set_allocated_salebooth(::HelloKittyMsgData::PbSaleBooth* salebooth) {
  delete salebooth_;
  salebooth_ = salebooth;
  if (salebooth) {
    set_has_salebooth();
  } else {
    clear_has_salebooth();
  }
}

// repeated .HelloKittyMsgData.Factor factor = 4;
inline int Serialize::factor_size() const {
  return factor_.size();
}
inline void Serialize::clear_factor() {
  factor_.Clear();
}
inline const ::HelloKittyMsgData::Factor& Serialize::factor(int index) const {
  return factor_.Get(index);
}
inline ::HelloKittyMsgData::Factor* Serialize::mutable_factor(int index) {
  return factor_.Mutable(index);
}
inline ::HelloKittyMsgData::Factor* Serialize::add_factor() {
  return factor_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::Factor >&
Serialize::factor() const {
  return factor_;
}
inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::Factor >*
Serialize::mutable_factor() {
  return &factor_;
}

// -------------------------------------------------------------------

// MsgSaleCell

// repeated .HelloKittyMsgData.PbCounter pb_counters = 1;
inline int MsgSaleCell::pb_counters_size() const {
  return pb_counters_.size();
}
inline void MsgSaleCell::clear_pb_counters() {
  pb_counters_.Clear();
}
inline const ::HelloKittyMsgData::PbCounter& MsgSaleCell::pb_counters(int index) const {
  return pb_counters_.Get(index);
}
inline ::HelloKittyMsgData::PbCounter* MsgSaleCell::mutable_pb_counters(int index) {
  return pb_counters_.Mutable(index);
}
inline ::HelloKittyMsgData::PbCounter* MsgSaleCell::add_pb_counters() {
  return pb_counters_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbCounter >&
MsgSaleCell::pb_counters() const {
  return pb_counters_;
}
inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbCounter >*
MsgSaleCell::mutable_pb_counters() {
  return &pb_counters_;
}

// repeated .HelloKittyMsgData.PbStoreItem store_items = 2;
inline int MsgSaleCell::store_items_size() const {
  return store_items_.size();
}
inline void MsgSaleCell::clear_store_items() {
  store_items_.Clear();
}
inline const ::HelloKittyMsgData::PbStoreItem& MsgSaleCell::store_items(int index) const {
  return store_items_.Get(index);
}
inline ::HelloKittyMsgData::PbStoreItem* MsgSaleCell::mutable_store_items(int index) {
  return store_items_.Mutable(index);
}
inline ::HelloKittyMsgData::PbStoreItem* MsgSaleCell::add_store_items() {
  return store_items_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbStoreItem >&
MsgSaleCell::store_items() const {
  return store_items_;
}
inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::PbStoreItem >*
MsgSaleCell::mutable_store_items() {
  return &store_items_;
}

// optional .HelloKittyMsgData.PbSaleBooth saleBooth = 3;
inline bool MsgSaleCell::has_salebooth() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MsgSaleCell::set_has_salebooth() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MsgSaleCell::clear_has_salebooth() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MsgSaleCell::clear_salebooth() {
  if (salebooth_ != NULL) salebooth_->::HelloKittyMsgData::PbSaleBooth::Clear();
  clear_has_salebooth();
}
inline const ::HelloKittyMsgData::PbSaleBooth& MsgSaleCell::salebooth() const {
  return salebooth_ != NULL ? *salebooth_ : *default_instance_->salebooth_;
}
inline ::HelloKittyMsgData::PbSaleBooth* MsgSaleCell::mutable_salebooth() {
  set_has_salebooth();
  if (salebooth_ == NULL) salebooth_ = new ::HelloKittyMsgData::PbSaleBooth;
  return salebooth_;
}
inline ::HelloKittyMsgData::PbSaleBooth* MsgSaleCell::release_salebooth() {
  clear_has_salebooth();
  ::HelloKittyMsgData::PbSaleBooth* temp = salebooth_;
  salebooth_ = NULL;
  return temp;
}
inline void MsgSaleCell::set_allocated_salebooth(::HelloKittyMsgData::PbSaleBooth* salebooth) {
  delete salebooth_;
  salebooth_ = salebooth;
  if (salebooth) {
    set_has_salebooth();
  } else {
    clear_has_salebooth();
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace HelloKittyMsgData

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::HelloKittyMsgData::CounterResetType>() {
  return ::HelloKittyMsgData::CounterResetType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_serialize_2eproto__INCLUDED
