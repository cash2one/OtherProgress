// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: burstevent.proto

#ifndef PROTOBUF_burstevent_2eproto__INCLUDED
#define PROTOBUF_burstevent_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace HelloKittyMsgData {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_burstevent_2eproto();
void protobuf_AssignDesc_burstevent_2eproto();
void protobuf_ShutdownFile_burstevent_2eproto();

class BurstEvent;
class ReqBurstEvent;
class AckUpdateBurstEvent;
class ReqOpBurstEvent;

enum BurstEventStatus {
  BES_Accept = 0,
  BES_Del_Finish = 1,
  BES_Del_Road = 2,
  BES_Del_Other = 3
};
bool BurstEventStatus_IsValid(int value);
const BurstEventStatus BurstEventStatus_MIN = BES_Accept;
const BurstEventStatus BurstEventStatus_MAX = BES_Del_Other;
const int BurstEventStatus_ARRAYSIZE = BurstEventStatus_MAX + 1;

const ::google::protobuf::EnumDescriptor* BurstEventStatus_descriptor();
inline const ::std::string& BurstEventStatus_Name(BurstEventStatus value) {
  return ::google::protobuf::internal::NameOfEnum(
    BurstEventStatus_descriptor(), value);
}
inline bool BurstEventStatus_Parse(
    const ::std::string& name, BurstEventStatus* value) {
  return ::google::protobuf::internal::ParseNamedEnum<BurstEventStatus>(
    BurstEventStatus_descriptor(), name, value);
}
enum BurstEventOpType {
  BEOT_Submit = 0,
  BEOT_Object = 1
};
bool BurstEventOpType_IsValid(int value);
const BurstEventOpType BurstEventOpType_MIN = BEOT_Submit;
const BurstEventOpType BurstEventOpType_MAX = BEOT_Object;
const int BurstEventOpType_ARRAYSIZE = BurstEventOpType_MAX + 1;

const ::google::protobuf::EnumDescriptor* BurstEventOpType_descriptor();
inline const ::std::string& BurstEventOpType_Name(BurstEventOpType value) {
  return ::google::protobuf::internal::NameOfEnum(
    BurstEventOpType_descriptor(), value);
}
inline bool BurstEventOpType_Parse(
    const ::std::string& name, BurstEventOpType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<BurstEventOpType>(
    BurstEventOpType_descriptor(), name, value);
}
// ===================================================================

class BurstEvent : public ::google::protobuf::Message {
 public:
  BurstEvent();
  virtual ~BurstEvent();

  BurstEvent(const BurstEvent& from);

  inline BurstEvent& operator=(const BurstEvent& from) {
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
  static const BurstEvent& default_instance();

  void Swap(BurstEvent* other);

  // implements Message ----------------------------------------------

  BurstEvent* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BurstEvent& from);
  void MergeFrom(const BurstEvent& from);
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

  // required uint64 tempid = 1;
  inline bool has_tempid() const;
  inline void clear_tempid();
  static const int kTempidFieldNumber = 1;
  inline ::google::protobuf::uint64 tempid() const;
  inline void set_tempid(::google::protobuf::uint64 value);

  // required uint32 npckey = 2;
  inline bool has_npckey() const;
  inline void clear_npckey();
  static const int kNpckeyFieldNumber = 2;
  inline ::google::protobuf::uint32 npckey() const;
  inline void set_npckey(::google::protobuf::uint32 value);

  // required uint32 rewardkey = 3;
  inline bool has_rewardkey() const;
  inline void clear_rewardkey();
  static const int kRewardkeyFieldNumber = 3;
  inline ::google::protobuf::uint32 rewardkey() const;
  inline void set_rewardkey(::google::protobuf::uint32 value);

  // required .HelloKittyMsgData.BurstEventStatus status = 4;
  inline bool has_status() const;
  inline void clear_status();
  static const int kStatusFieldNumber = 4;
  inline ::HelloKittyMsgData::BurstEventStatus status() const;
  inline void set_status(::HelloKittyMsgData::BurstEventStatus value);

  // required uint32 begintime = 5;
  inline bool has_begintime() const;
  inline void clear_begintime();
  static const int kBegintimeFieldNumber = 5;
  inline ::google::protobuf::uint32 begintime() const;
  inline void set_begintime(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.BurstEvent)
 private:
  inline void set_has_tempid();
  inline void clear_has_tempid();
  inline void set_has_npckey();
  inline void clear_has_npckey();
  inline void set_has_rewardkey();
  inline void clear_has_rewardkey();
  inline void set_has_status();
  inline void clear_has_status();
  inline void set_has_begintime();
  inline void clear_has_begintime();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint64 tempid_;
  ::google::protobuf::uint32 npckey_;
  ::google::protobuf::uint32 rewardkey_;
  int status_;
  ::google::protobuf::uint32 begintime_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];

  friend void  protobuf_AddDesc_burstevent_2eproto();
  friend void protobuf_AssignDesc_burstevent_2eproto();
  friend void protobuf_ShutdownFile_burstevent_2eproto();

  void InitAsDefaultInstance();
  static BurstEvent* default_instance_;
};
// -------------------------------------------------------------------

class ReqBurstEvent : public ::google::protobuf::Message {
 public:
  ReqBurstEvent();
  virtual ~ReqBurstEvent();

  ReqBurstEvent(const ReqBurstEvent& from);

  inline ReqBurstEvent& operator=(const ReqBurstEvent& from) {
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
  static const ReqBurstEvent& default_instance();

  void Swap(ReqBurstEvent* other);

  // implements Message ----------------------------------------------

  ReqBurstEvent* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ReqBurstEvent& from);
  void MergeFrom(const ReqBurstEvent& from);
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

  // optional uint64 tempid = 1 [default = 0];
  inline bool has_tempid() const;
  inline void clear_tempid();
  static const int kTempidFieldNumber = 1;
  inline ::google::protobuf::uint64 tempid() const;
  inline void set_tempid(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.ReqBurstEvent)
 private:
  inline void set_has_tempid();
  inline void clear_has_tempid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint64 tempid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_burstevent_2eproto();
  friend void protobuf_AssignDesc_burstevent_2eproto();
  friend void protobuf_ShutdownFile_burstevent_2eproto();

  void InitAsDefaultInstance();
  static ReqBurstEvent* default_instance_;
};
// -------------------------------------------------------------------

class AckUpdateBurstEvent : public ::google::protobuf::Message {
 public:
  AckUpdateBurstEvent();
  virtual ~AckUpdateBurstEvent();

  AckUpdateBurstEvent(const AckUpdateBurstEvent& from);

  inline AckUpdateBurstEvent& operator=(const AckUpdateBurstEvent& from) {
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
  static const AckUpdateBurstEvent& default_instance();

  void Swap(AckUpdateBurstEvent* other);

  // implements Message ----------------------------------------------

  AckUpdateBurstEvent* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AckUpdateBurstEvent& from);
  void MergeFrom(const AckUpdateBurstEvent& from);
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

  // repeated .HelloKittyMsgData.BurstEvent eventList = 1;
  inline int eventlist_size() const;
  inline void clear_eventlist();
  static const int kEventListFieldNumber = 1;
  inline const ::HelloKittyMsgData::BurstEvent& eventlist(int index) const;
  inline ::HelloKittyMsgData::BurstEvent* mutable_eventlist(int index);
  inline ::HelloKittyMsgData::BurstEvent* add_eventlist();
  inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::BurstEvent >&
      eventlist() const;
  inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::BurstEvent >*
      mutable_eventlist();

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.AckUpdateBurstEvent)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::BurstEvent > eventlist_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_burstevent_2eproto();
  friend void protobuf_AssignDesc_burstevent_2eproto();
  friend void protobuf_ShutdownFile_burstevent_2eproto();

  void InitAsDefaultInstance();
  static AckUpdateBurstEvent* default_instance_;
};
// -------------------------------------------------------------------

class ReqOpBurstEvent : public ::google::protobuf::Message {
 public:
  ReqOpBurstEvent();
  virtual ~ReqOpBurstEvent();

  ReqOpBurstEvent(const ReqOpBurstEvent& from);

  inline ReqOpBurstEvent& operator=(const ReqOpBurstEvent& from) {
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
  static const ReqOpBurstEvent& default_instance();

  void Swap(ReqOpBurstEvent* other);

  // implements Message ----------------------------------------------

  ReqOpBurstEvent* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ReqOpBurstEvent& from);
  void MergeFrom(const ReqOpBurstEvent& from);
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

  // required uint64 tempid = 1;
  inline bool has_tempid() const;
  inline void clear_tempid();
  static const int kTempidFieldNumber = 1;
  inline ::google::protobuf::uint64 tempid() const;
  inline void set_tempid(::google::protobuf::uint64 value);

  // required .HelloKittyMsgData.BurstEventOpType optype = 2;
  inline bool has_optype() const;
  inline void clear_optype();
  static const int kOptypeFieldNumber = 2;
  inline ::HelloKittyMsgData::BurstEventOpType optype() const;
  inline void set_optype(::HelloKittyMsgData::BurstEventOpType value);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.ReqOpBurstEvent)
 private:
  inline void set_has_tempid();
  inline void clear_has_tempid();
  inline void set_has_optype();
  inline void clear_has_optype();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint64 tempid_;
  int optype_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_burstevent_2eproto();
  friend void protobuf_AssignDesc_burstevent_2eproto();
  friend void protobuf_ShutdownFile_burstevent_2eproto();

  void InitAsDefaultInstance();
  static ReqOpBurstEvent* default_instance_;
};
// ===================================================================


// ===================================================================

// BurstEvent

// required uint64 tempid = 1;
inline bool BurstEvent::has_tempid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BurstEvent::set_has_tempid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BurstEvent::clear_has_tempid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BurstEvent::clear_tempid() {
  tempid_ = GOOGLE_ULONGLONG(0);
  clear_has_tempid();
}
inline ::google::protobuf::uint64 BurstEvent::tempid() const {
  return tempid_;
}
inline void BurstEvent::set_tempid(::google::protobuf::uint64 value) {
  set_has_tempid();
  tempid_ = value;
}

// required uint32 npckey = 2;
inline bool BurstEvent::has_npckey() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BurstEvent::set_has_npckey() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BurstEvent::clear_has_npckey() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BurstEvent::clear_npckey() {
  npckey_ = 0u;
  clear_has_npckey();
}
inline ::google::protobuf::uint32 BurstEvent::npckey() const {
  return npckey_;
}
inline void BurstEvent::set_npckey(::google::protobuf::uint32 value) {
  set_has_npckey();
  npckey_ = value;
}

// required uint32 rewardkey = 3;
inline bool BurstEvent::has_rewardkey() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void BurstEvent::set_has_rewardkey() {
  _has_bits_[0] |= 0x00000004u;
}
inline void BurstEvent::clear_has_rewardkey() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void BurstEvent::clear_rewardkey() {
  rewardkey_ = 0u;
  clear_has_rewardkey();
}
inline ::google::protobuf::uint32 BurstEvent::rewardkey() const {
  return rewardkey_;
}
inline void BurstEvent::set_rewardkey(::google::protobuf::uint32 value) {
  set_has_rewardkey();
  rewardkey_ = value;
}

// required .HelloKittyMsgData.BurstEventStatus status = 4;
inline bool BurstEvent::has_status() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void BurstEvent::set_has_status() {
  _has_bits_[0] |= 0x00000008u;
}
inline void BurstEvent::clear_has_status() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void BurstEvent::clear_status() {
  status_ = 0;
  clear_has_status();
}
inline ::HelloKittyMsgData::BurstEventStatus BurstEvent::status() const {
  return static_cast< ::HelloKittyMsgData::BurstEventStatus >(status_);
}
inline void BurstEvent::set_status(::HelloKittyMsgData::BurstEventStatus value) {
  assert(::HelloKittyMsgData::BurstEventStatus_IsValid(value));
  set_has_status();
  status_ = value;
}

// required uint32 begintime = 5;
inline bool BurstEvent::has_begintime() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void BurstEvent::set_has_begintime() {
  _has_bits_[0] |= 0x00000010u;
}
inline void BurstEvent::clear_has_begintime() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void BurstEvent::clear_begintime() {
  begintime_ = 0u;
  clear_has_begintime();
}
inline ::google::protobuf::uint32 BurstEvent::begintime() const {
  return begintime_;
}
inline void BurstEvent::set_begintime(::google::protobuf::uint32 value) {
  set_has_begintime();
  begintime_ = value;
}

// -------------------------------------------------------------------

// ReqBurstEvent

// optional uint64 tempid = 1 [default = 0];
inline bool ReqBurstEvent::has_tempid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ReqBurstEvent::set_has_tempid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ReqBurstEvent::clear_has_tempid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ReqBurstEvent::clear_tempid() {
  tempid_ = GOOGLE_ULONGLONG(0);
  clear_has_tempid();
}
inline ::google::protobuf::uint64 ReqBurstEvent::tempid() const {
  return tempid_;
}
inline void ReqBurstEvent::set_tempid(::google::protobuf::uint64 value) {
  set_has_tempid();
  tempid_ = value;
}

// -------------------------------------------------------------------

// AckUpdateBurstEvent

// repeated .HelloKittyMsgData.BurstEvent eventList = 1;
inline int AckUpdateBurstEvent::eventlist_size() const {
  return eventlist_.size();
}
inline void AckUpdateBurstEvent::clear_eventlist() {
  eventlist_.Clear();
}
inline const ::HelloKittyMsgData::BurstEvent& AckUpdateBurstEvent::eventlist(int index) const {
  return eventlist_.Get(index);
}
inline ::HelloKittyMsgData::BurstEvent* AckUpdateBurstEvent::mutable_eventlist(int index) {
  return eventlist_.Mutable(index);
}
inline ::HelloKittyMsgData::BurstEvent* AckUpdateBurstEvent::add_eventlist() {
  return eventlist_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::BurstEvent >&
AckUpdateBurstEvent::eventlist() const {
  return eventlist_;
}
inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::BurstEvent >*
AckUpdateBurstEvent::mutable_eventlist() {
  return &eventlist_;
}

// -------------------------------------------------------------------

// ReqOpBurstEvent

// required uint64 tempid = 1;
inline bool ReqOpBurstEvent::has_tempid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ReqOpBurstEvent::set_has_tempid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ReqOpBurstEvent::clear_has_tempid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ReqOpBurstEvent::clear_tempid() {
  tempid_ = GOOGLE_ULONGLONG(0);
  clear_has_tempid();
}
inline ::google::protobuf::uint64 ReqOpBurstEvent::tempid() const {
  return tempid_;
}
inline void ReqOpBurstEvent::set_tempid(::google::protobuf::uint64 value) {
  set_has_tempid();
  tempid_ = value;
}

// required .HelloKittyMsgData.BurstEventOpType optype = 2;
inline bool ReqOpBurstEvent::has_optype() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ReqOpBurstEvent::set_has_optype() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ReqOpBurstEvent::clear_has_optype() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ReqOpBurstEvent::clear_optype() {
  optype_ = 0;
  clear_has_optype();
}
inline ::HelloKittyMsgData::BurstEventOpType ReqOpBurstEvent::optype() const {
  return static_cast< ::HelloKittyMsgData::BurstEventOpType >(optype_);
}
inline void ReqOpBurstEvent::set_optype(::HelloKittyMsgData::BurstEventOpType value) {
  assert(::HelloKittyMsgData::BurstEventOpType_IsValid(value));
  set_has_optype();
  optype_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace HelloKittyMsgData

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::HelloKittyMsgData::BurstEventStatus>() {
  return ::HelloKittyMsgData::BurstEventStatus_descriptor();
}
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::HelloKittyMsgData::BurstEventOpType>() {
  return ::HelloKittyMsgData::BurstEventOpType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_burstevent_2eproto__INCLUDED