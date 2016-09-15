// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: usecardbuild.proto

#ifndef PROTOBUF_usecardbuild_2eproto__INCLUDED
#define PROTOBUF_usecardbuild_2eproto__INCLUDED

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
void  protobuf_AddDesc_usecardbuild_2eproto();
void protobuf_AssignDesc_usecardbuild_2eproto();
void protobuf_ShutdownFile_usecardbuild_2eproto();

class UseCardInfo;
class ReqOpCard;
class AckUpdateCard;
class ReqUserCard;

enum BuildCardOpType {
  BCO_Req = 0,
  BCO_Del = 1
};
bool BuildCardOpType_IsValid(int value);
const BuildCardOpType BuildCardOpType_MIN = BCO_Req;
const BuildCardOpType BuildCardOpType_MAX = BCO_Del;
const int BuildCardOpType_ARRAYSIZE = BuildCardOpType_MAX + 1;

const ::google::protobuf::EnumDescriptor* BuildCardOpType_descriptor();
inline const ::std::string& BuildCardOpType_Name(BuildCardOpType value) {
  return ::google::protobuf::internal::NameOfEnum(
    BuildCardOpType_descriptor(), value);
}
inline bool BuildCardOpType_Parse(
    const ::std::string& name, BuildCardOpType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<BuildCardOpType>(
    BuildCardOpType_descriptor(), name, value);
}
// ===================================================================

class UseCardInfo : public ::google::protobuf::Message {
 public:
  UseCardInfo();
  virtual ~UseCardInfo();

  UseCardInfo(const UseCardInfo& from);

  inline UseCardInfo& operator=(const UseCardInfo& from) {
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
  static const UseCardInfo& default_instance();

  void Swap(UseCardInfo* other);

  // implements Message ----------------------------------------------

  UseCardInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UseCardInfo& from);
  void MergeFrom(const UseCardInfo& from);
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

  // required uint32 cardid = 2;
  inline bool has_cardid() const;
  inline void clear_cardid();
  static const int kCardidFieldNumber = 2;
  inline ::google::protobuf::uint32 cardid() const;
  inline void set_cardid(::google::protobuf::uint32 value);

  // required uint32 usecardtime = 3;
  inline bool has_usecardtime() const;
  inline void clear_usecardtime();
  static const int kUsecardtimeFieldNumber = 3;
  inline ::google::protobuf::uint32 usecardtime() const;
  inline void set_usecardtime(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.UseCardInfo)
 private:
  inline void set_has_tempid();
  inline void clear_has_tempid();
  inline void set_has_cardid();
  inline void clear_has_cardid();
  inline void set_has_usecardtime();
  inline void clear_has_usecardtime();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint64 tempid_;
  ::google::protobuf::uint32 cardid_;
  ::google::protobuf::uint32 usecardtime_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_usecardbuild_2eproto();
  friend void protobuf_AssignDesc_usecardbuild_2eproto();
  friend void protobuf_ShutdownFile_usecardbuild_2eproto();

  void InitAsDefaultInstance();
  static UseCardInfo* default_instance_;
};
// -------------------------------------------------------------------

class ReqOpCard : public ::google::protobuf::Message {
 public:
  ReqOpCard();
  virtual ~ReqOpCard();

  ReqOpCard(const ReqOpCard& from);

  inline ReqOpCard& operator=(const ReqOpCard& from) {
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
  static const ReqOpCard& default_instance();

  void Swap(ReqOpCard* other);

  // implements Message ----------------------------------------------

  ReqOpCard* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ReqOpCard& from);
  void MergeFrom(const ReqOpCard& from);
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

  // required .HelloKittyMsgData.BuildCardOpType optype = 2;
  inline bool has_optype() const;
  inline void clear_optype();
  static const int kOptypeFieldNumber = 2;
  inline ::HelloKittyMsgData::BuildCardOpType optype() const;
  inline void set_optype(::HelloKittyMsgData::BuildCardOpType value);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.ReqOpCard)
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

  friend void  protobuf_AddDesc_usecardbuild_2eproto();
  friend void protobuf_AssignDesc_usecardbuild_2eproto();
  friend void protobuf_ShutdownFile_usecardbuild_2eproto();

  void InitAsDefaultInstance();
  static ReqOpCard* default_instance_;
};
// -------------------------------------------------------------------

class AckUpdateCard : public ::google::protobuf::Message {
 public:
  AckUpdateCard();
  virtual ~AckUpdateCard();

  AckUpdateCard(const AckUpdateCard& from);

  inline AckUpdateCard& operator=(const AckUpdateCard& from) {
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
  static const AckUpdateCard& default_instance();

  void Swap(AckUpdateCard* other);

  // implements Message ----------------------------------------------

  AckUpdateCard* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AckUpdateCard& from);
  void MergeFrom(const AckUpdateCard& from);
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

  // required .HelloKittyMsgData.UseCardInfo cardinfo = 1;
  inline bool has_cardinfo() const;
  inline void clear_cardinfo();
  static const int kCardinfoFieldNumber = 1;
  inline const ::HelloKittyMsgData::UseCardInfo& cardinfo() const;
  inline ::HelloKittyMsgData::UseCardInfo* mutable_cardinfo();
  inline ::HelloKittyMsgData::UseCardInfo* release_cardinfo();
  inline void set_allocated_cardinfo(::HelloKittyMsgData::UseCardInfo* cardinfo);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.AckUpdateCard)
 private:
  inline void set_has_cardinfo();
  inline void clear_has_cardinfo();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::HelloKittyMsgData::UseCardInfo* cardinfo_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_usecardbuild_2eproto();
  friend void protobuf_AssignDesc_usecardbuild_2eproto();
  friend void protobuf_ShutdownFile_usecardbuild_2eproto();

  void InitAsDefaultInstance();
  static AckUpdateCard* default_instance_;
};
// -------------------------------------------------------------------

class ReqUserCard : public ::google::protobuf::Message {
 public:
  ReqUserCard();
  virtual ~ReqUserCard();

  ReqUserCard(const ReqUserCard& from);

  inline ReqUserCard& operator=(const ReqUserCard& from) {
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
  static const ReqUserCard& default_instance();

  void Swap(ReqUserCard* other);

  // implements Message ----------------------------------------------

  ReqUserCard* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ReqUserCard& from);
  void MergeFrom(const ReqUserCard& from);
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

  // required uint32 item = 2;
  inline bool has_item() const;
  inline void clear_item();
  static const int kItemFieldNumber = 2;
  inline ::google::protobuf::uint32 item() const;
  inline void set_item(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.ReqUserCard)
 private:
  inline void set_has_tempid();
  inline void clear_has_tempid();
  inline void set_has_item();
  inline void clear_has_item();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint64 tempid_;
  ::google::protobuf::uint32 item_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_usecardbuild_2eproto();
  friend void protobuf_AssignDesc_usecardbuild_2eproto();
  friend void protobuf_ShutdownFile_usecardbuild_2eproto();

  void InitAsDefaultInstance();
  static ReqUserCard* default_instance_;
};
// ===================================================================


// ===================================================================

// UseCardInfo

// required uint64 tempid = 1;
inline bool UseCardInfo::has_tempid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UseCardInfo::set_has_tempid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UseCardInfo::clear_has_tempid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UseCardInfo::clear_tempid() {
  tempid_ = GOOGLE_ULONGLONG(0);
  clear_has_tempid();
}
inline ::google::protobuf::uint64 UseCardInfo::tempid() const {
  return tempid_;
}
inline void UseCardInfo::set_tempid(::google::protobuf::uint64 value) {
  set_has_tempid();
  tempid_ = value;
}

// required uint32 cardid = 2;
inline bool UseCardInfo::has_cardid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UseCardInfo::set_has_cardid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UseCardInfo::clear_has_cardid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UseCardInfo::clear_cardid() {
  cardid_ = 0u;
  clear_has_cardid();
}
inline ::google::protobuf::uint32 UseCardInfo::cardid() const {
  return cardid_;
}
inline void UseCardInfo::set_cardid(::google::protobuf::uint32 value) {
  set_has_cardid();
  cardid_ = value;
}

// required uint32 usecardtime = 3;
inline bool UseCardInfo::has_usecardtime() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void UseCardInfo::set_has_usecardtime() {
  _has_bits_[0] |= 0x00000004u;
}
inline void UseCardInfo::clear_has_usecardtime() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void UseCardInfo::clear_usecardtime() {
  usecardtime_ = 0u;
  clear_has_usecardtime();
}
inline ::google::protobuf::uint32 UseCardInfo::usecardtime() const {
  return usecardtime_;
}
inline void UseCardInfo::set_usecardtime(::google::protobuf::uint32 value) {
  set_has_usecardtime();
  usecardtime_ = value;
}

// -------------------------------------------------------------------

// ReqOpCard

// required uint64 tempid = 1;
inline bool ReqOpCard::has_tempid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ReqOpCard::set_has_tempid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ReqOpCard::clear_has_tempid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ReqOpCard::clear_tempid() {
  tempid_ = GOOGLE_ULONGLONG(0);
  clear_has_tempid();
}
inline ::google::protobuf::uint64 ReqOpCard::tempid() const {
  return tempid_;
}
inline void ReqOpCard::set_tempid(::google::protobuf::uint64 value) {
  set_has_tempid();
  tempid_ = value;
}

// required .HelloKittyMsgData.BuildCardOpType optype = 2;
inline bool ReqOpCard::has_optype() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ReqOpCard::set_has_optype() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ReqOpCard::clear_has_optype() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ReqOpCard::clear_optype() {
  optype_ = 0;
  clear_has_optype();
}
inline ::HelloKittyMsgData::BuildCardOpType ReqOpCard::optype() const {
  return static_cast< ::HelloKittyMsgData::BuildCardOpType >(optype_);
}
inline void ReqOpCard::set_optype(::HelloKittyMsgData::BuildCardOpType value) {
  assert(::HelloKittyMsgData::BuildCardOpType_IsValid(value));
  set_has_optype();
  optype_ = value;
}

// -------------------------------------------------------------------

// AckUpdateCard

// required .HelloKittyMsgData.UseCardInfo cardinfo = 1;
inline bool AckUpdateCard::has_cardinfo() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AckUpdateCard::set_has_cardinfo() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AckUpdateCard::clear_has_cardinfo() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AckUpdateCard::clear_cardinfo() {
  if (cardinfo_ != NULL) cardinfo_->::HelloKittyMsgData::UseCardInfo::Clear();
  clear_has_cardinfo();
}
inline const ::HelloKittyMsgData::UseCardInfo& AckUpdateCard::cardinfo() const {
  return cardinfo_ != NULL ? *cardinfo_ : *default_instance_->cardinfo_;
}
inline ::HelloKittyMsgData::UseCardInfo* AckUpdateCard::mutable_cardinfo() {
  set_has_cardinfo();
  if (cardinfo_ == NULL) cardinfo_ = new ::HelloKittyMsgData::UseCardInfo;
  return cardinfo_;
}
inline ::HelloKittyMsgData::UseCardInfo* AckUpdateCard::release_cardinfo() {
  clear_has_cardinfo();
  ::HelloKittyMsgData::UseCardInfo* temp = cardinfo_;
  cardinfo_ = NULL;
  return temp;
}
inline void AckUpdateCard::set_allocated_cardinfo(::HelloKittyMsgData::UseCardInfo* cardinfo) {
  delete cardinfo_;
  cardinfo_ = cardinfo;
  if (cardinfo) {
    set_has_cardinfo();
  } else {
    clear_has_cardinfo();
  }
}

// -------------------------------------------------------------------

// ReqUserCard

// required uint64 tempid = 1;
inline bool ReqUserCard::has_tempid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ReqUserCard::set_has_tempid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ReqUserCard::clear_has_tempid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ReqUserCard::clear_tempid() {
  tempid_ = GOOGLE_ULONGLONG(0);
  clear_has_tempid();
}
inline ::google::protobuf::uint64 ReqUserCard::tempid() const {
  return tempid_;
}
inline void ReqUserCard::set_tempid(::google::protobuf::uint64 value) {
  set_has_tempid();
  tempid_ = value;
}

// required uint32 item = 2;
inline bool ReqUserCard::has_item() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ReqUserCard::set_has_item() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ReqUserCard::clear_has_item() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ReqUserCard::clear_item() {
  item_ = 0u;
  clear_has_item();
}
inline ::google::protobuf::uint32 ReqUserCard::item() const {
  return item_;
}
inline void ReqUserCard::set_item(::google::protobuf::uint32 value) {
  set_has_item();
  item_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace HelloKittyMsgData

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::HelloKittyMsgData::BuildCardOpType>() {
  return ::HelloKittyMsgData::BuildCardOpType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_usecardbuild_2eproto__INCLUDED