// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: divine.proto

#ifndef PROTOBUF_divine_2eproto__INCLUDED
#define PROTOBUF_divine_2eproto__INCLUDED

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
void  protobuf_AddDesc_divine_2eproto();
void protobuf_AssignDesc_divine_2eproto();
void protobuf_ShutdownFile_divine_2eproto();

class DivineData;
class ReqDivineInfo;
class ReqDivineNotice;
class ReqDivine;
class AckDivine;
class ReqDivineVerify;

enum DivineStatus {
  DS_Begin = 0,
  DS_Vertify = 1,
  DS_End = 2
};
bool DivineStatus_IsValid(int value);
const DivineStatus DivineStatus_MIN = DS_Begin;
const DivineStatus DivineStatus_MAX = DS_End;
const int DivineStatus_ARRAYSIZE = DivineStatus_MAX + 1;

const ::google::protobuf::EnumDescriptor* DivineStatus_descriptor();
inline const ::std::string& DivineStatus_Name(DivineStatus value) {
  return ::google::protobuf::internal::NameOfEnum(
    DivineStatus_descriptor(), value);
}
inline bool DivineStatus_Parse(
    const ::std::string& name, DivineStatus* value) {
  return ::google::protobuf::internal::ParseNamedEnum<DivineStatus>(
    DivineStatus_descriptor(), name, value);
}
// ===================================================================

class DivineData : public ::google::protobuf::Message {
 public:
  DivineData();
  virtual ~DivineData();

  DivineData(const DivineData& from);

  inline DivineData& operator=(const DivineData& from) {
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
  static const DivineData& default_instance();

  void Swap(DivineData* other);

  // implements Message ----------------------------------------------

  DivineData* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DivineData& from);
  void MergeFrom(const DivineData& from);
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

  // required uint32 answer = 1;
  inline bool has_answer() const;
  inline void clear_answer();
  static const int kAnswerFieldNumber = 1;
  inline ::google::protobuf::uint32 answer() const;
  inline void set_answer(::google::protobuf::uint32 value);

  // required uint32 lucklevel = 2;
  inline bool has_lucklevel() const;
  inline void clear_lucklevel();
  static const int kLucklevelFieldNumber = 2;
  inline ::google::protobuf::uint32 lucklevel() const;
  inline void set_lucklevel(::google::protobuf::uint32 value);

  // required string randorder = 3;
  inline bool has_randorder() const;
  inline void clear_randorder();
  static const int kRandorderFieldNumber = 3;
  inline const ::std::string& randorder() const;
  inline void set_randorder(const ::std::string& value);
  inline void set_randorder(const char* value);
  inline void set_randorder(const char* value, size_t size);
  inline ::std::string* mutable_randorder();
  inline ::std::string* release_randorder();
  inline void set_allocated_randorder(::std::string* randorder);

  // required uint32 randtime = 4;
  inline bool has_randtime() const;
  inline void clear_randtime();
  static const int kRandtimeFieldNumber = 4;
  inline ::google::protobuf::uint32 randtime() const;
  inline void set_randtime(::google::protobuf::uint32 value);

  // required uint32 firstkey = 5;
  inline bool has_firstkey() const;
  inline void clear_firstkey();
  static const int kFirstkeyFieldNumber = 5;
  inline ::google::protobuf::uint32 firstkey() const;
  inline void set_firstkey(::google::protobuf::uint32 value);

  // required .HelloKittyMsgData.DivineStatus status = 6;
  inline bool has_status() const;
  inline void clear_status();
  static const int kStatusFieldNumber = 6;
  inline ::HelloKittyMsgData::DivineStatus status() const;
  inline void set_status(::HelloKittyMsgData::DivineStatus value);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.DivineData)
 private:
  inline void set_has_answer();
  inline void clear_has_answer();
  inline void set_has_lucklevel();
  inline void clear_has_lucklevel();
  inline void set_has_randorder();
  inline void clear_has_randorder();
  inline void set_has_randtime();
  inline void clear_has_randtime();
  inline void set_has_firstkey();
  inline void clear_has_firstkey();
  inline void set_has_status();
  inline void clear_has_status();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 answer_;
  ::google::protobuf::uint32 lucklevel_;
  ::std::string* randorder_;
  ::google::protobuf::uint32 randtime_;
  ::google::protobuf::uint32 firstkey_;
  int status_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(6 + 31) / 32];

  friend void  protobuf_AddDesc_divine_2eproto();
  friend void protobuf_AssignDesc_divine_2eproto();
  friend void protobuf_ShutdownFile_divine_2eproto();

  void InitAsDefaultInstance();
  static DivineData* default_instance_;
};
// -------------------------------------------------------------------

class ReqDivineInfo : public ::google::protobuf::Message {
 public:
  ReqDivineInfo();
  virtual ~ReqDivineInfo();

  ReqDivineInfo(const ReqDivineInfo& from);

  inline ReqDivineInfo& operator=(const ReqDivineInfo& from) {
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
  static const ReqDivineInfo& default_instance();

  void Swap(ReqDivineInfo* other);

  // implements Message ----------------------------------------------

  ReqDivineInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ReqDivineInfo& from);
  void MergeFrom(const ReqDivineInfo& from);
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

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.ReqDivineInfo)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;


  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[1];

  friend void  protobuf_AddDesc_divine_2eproto();
  friend void protobuf_AssignDesc_divine_2eproto();
  friend void protobuf_ShutdownFile_divine_2eproto();

  void InitAsDefaultInstance();
  static ReqDivineInfo* default_instance_;
};
// -------------------------------------------------------------------

class ReqDivineNotice : public ::google::protobuf::Message {
 public:
  ReqDivineNotice();
  virtual ~ReqDivineNotice();

  ReqDivineNotice(const ReqDivineNotice& from);

  inline ReqDivineNotice& operator=(const ReqDivineNotice& from) {
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
  static const ReqDivineNotice& default_instance();

  void Swap(ReqDivineNotice* other);

  // implements Message ----------------------------------------------

  ReqDivineNotice* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ReqDivineNotice& from);
  void MergeFrom(const ReqDivineNotice& from);
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

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.ReqDivineNotice)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;


  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[1];

  friend void  protobuf_AddDesc_divine_2eproto();
  friend void protobuf_AssignDesc_divine_2eproto();
  friend void protobuf_ShutdownFile_divine_2eproto();

  void InitAsDefaultInstance();
  static ReqDivineNotice* default_instance_;
};
// -------------------------------------------------------------------

class ReqDivine : public ::google::protobuf::Message {
 public:
  ReqDivine();
  virtual ~ReqDivine();

  ReqDivine(const ReqDivine& from);

  inline ReqDivine& operator=(const ReqDivine& from) {
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
  static const ReqDivine& default_instance();

  void Swap(ReqDivine* other);

  // implements Message ----------------------------------------------

  ReqDivine* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ReqDivine& from);
  void MergeFrom(const ReqDivine& from);
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

  // required bool notify = 1;
  inline bool has_notify() const;
  inline void clear_notify();
  static const int kNotifyFieldNumber = 1;
  inline bool notify() const;
  inline void set_notify(bool value);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.ReqDivine)
 private:
  inline void set_has_notify();
  inline void clear_has_notify();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  bool notify_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_divine_2eproto();
  friend void protobuf_AssignDesc_divine_2eproto();
  friend void protobuf_ShutdownFile_divine_2eproto();

  void InitAsDefaultInstance();
  static ReqDivine* default_instance_;
};
// -------------------------------------------------------------------

class AckDivine : public ::google::protobuf::Message {
 public:
  AckDivine();
  virtual ~AckDivine();

  AckDivine(const AckDivine& from);

  inline AckDivine& operator=(const AckDivine& from) {
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
  static const AckDivine& default_instance();

  void Swap(AckDivine* other);

  // implements Message ----------------------------------------------

  AckDivine* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AckDivine& from);
  void MergeFrom(const AckDivine& from);
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

  // required .HelloKittyMsgData.DivineData divine = 1;
  inline bool has_divine() const;
  inline void clear_divine();
  static const int kDivineFieldNumber = 1;
  inline const ::HelloKittyMsgData::DivineData& divine() const;
  inline ::HelloKittyMsgData::DivineData* mutable_divine();
  inline ::HelloKittyMsgData::DivineData* release_divine();
  inline void set_allocated_divine(::HelloKittyMsgData::DivineData* divine);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.AckDivine)
 private:
  inline void set_has_divine();
  inline void clear_has_divine();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::HelloKittyMsgData::DivineData* divine_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_divine_2eproto();
  friend void protobuf_AssignDesc_divine_2eproto();
  friend void protobuf_ShutdownFile_divine_2eproto();

  void InitAsDefaultInstance();
  static AckDivine* default_instance_;
};
// -------------------------------------------------------------------

class ReqDivineVerify : public ::google::protobuf::Message {
 public:
  ReqDivineVerify();
  virtual ~ReqDivineVerify();

  ReqDivineVerify(const ReqDivineVerify& from);

  inline ReqDivineVerify& operator=(const ReqDivineVerify& from) {
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
  static const ReqDivineVerify& default_instance();

  void Swap(ReqDivineVerify* other);

  // implements Message ----------------------------------------------

  ReqDivineVerify* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ReqDivineVerify& from);
  void MergeFrom(const ReqDivineVerify& from);
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

  // required string older = 1;
  inline bool has_older() const;
  inline void clear_older();
  static const int kOlderFieldNumber = 1;
  inline const ::std::string& older() const;
  inline void set_older(const ::std::string& value);
  inline void set_older(const char* value);
  inline void set_older(const char* value, size_t size);
  inline ::std::string* mutable_older();
  inline ::std::string* release_older();
  inline void set_allocated_older(::std::string* older);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.ReqDivineVerify)
 private:
  inline void set_has_older();
  inline void clear_has_older();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* older_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_divine_2eproto();
  friend void protobuf_AssignDesc_divine_2eproto();
  friend void protobuf_ShutdownFile_divine_2eproto();

  void InitAsDefaultInstance();
  static ReqDivineVerify* default_instance_;
};
// ===================================================================


// ===================================================================

// DivineData

// required uint32 answer = 1;
inline bool DivineData::has_answer() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void DivineData::set_has_answer() {
  _has_bits_[0] |= 0x00000001u;
}
inline void DivineData::clear_has_answer() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void DivineData::clear_answer() {
  answer_ = 0u;
  clear_has_answer();
}
inline ::google::protobuf::uint32 DivineData::answer() const {
  return answer_;
}
inline void DivineData::set_answer(::google::protobuf::uint32 value) {
  set_has_answer();
  answer_ = value;
}

// required uint32 lucklevel = 2;
inline bool DivineData::has_lucklevel() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void DivineData::set_has_lucklevel() {
  _has_bits_[0] |= 0x00000002u;
}
inline void DivineData::clear_has_lucklevel() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void DivineData::clear_lucklevel() {
  lucklevel_ = 0u;
  clear_has_lucklevel();
}
inline ::google::protobuf::uint32 DivineData::lucklevel() const {
  return lucklevel_;
}
inline void DivineData::set_lucklevel(::google::protobuf::uint32 value) {
  set_has_lucklevel();
  lucklevel_ = value;
}

// required string randorder = 3;
inline bool DivineData::has_randorder() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void DivineData::set_has_randorder() {
  _has_bits_[0] |= 0x00000004u;
}
inline void DivineData::clear_has_randorder() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void DivineData::clear_randorder() {
  if (randorder_ != &::google::protobuf::internal::kEmptyString) {
    randorder_->clear();
  }
  clear_has_randorder();
}
inline const ::std::string& DivineData::randorder() const {
  return *randorder_;
}
inline void DivineData::set_randorder(const ::std::string& value) {
  set_has_randorder();
  if (randorder_ == &::google::protobuf::internal::kEmptyString) {
    randorder_ = new ::std::string;
  }
  randorder_->assign(value);
}
inline void DivineData::set_randorder(const char* value) {
  set_has_randorder();
  if (randorder_ == &::google::protobuf::internal::kEmptyString) {
    randorder_ = new ::std::string;
  }
  randorder_->assign(value);
}
inline void DivineData::set_randorder(const char* value, size_t size) {
  set_has_randorder();
  if (randorder_ == &::google::protobuf::internal::kEmptyString) {
    randorder_ = new ::std::string;
  }
  randorder_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* DivineData::mutable_randorder() {
  set_has_randorder();
  if (randorder_ == &::google::protobuf::internal::kEmptyString) {
    randorder_ = new ::std::string;
  }
  return randorder_;
}
inline ::std::string* DivineData::release_randorder() {
  clear_has_randorder();
  if (randorder_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = randorder_;
    randorder_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void DivineData::set_allocated_randorder(::std::string* randorder) {
  if (randorder_ != &::google::protobuf::internal::kEmptyString) {
    delete randorder_;
  }
  if (randorder) {
    set_has_randorder();
    randorder_ = randorder;
  } else {
    clear_has_randorder();
    randorder_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required uint32 randtime = 4;
inline bool DivineData::has_randtime() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void DivineData::set_has_randtime() {
  _has_bits_[0] |= 0x00000008u;
}
inline void DivineData::clear_has_randtime() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void DivineData::clear_randtime() {
  randtime_ = 0u;
  clear_has_randtime();
}
inline ::google::protobuf::uint32 DivineData::randtime() const {
  return randtime_;
}
inline void DivineData::set_randtime(::google::protobuf::uint32 value) {
  set_has_randtime();
  randtime_ = value;
}

// required uint32 firstkey = 5;
inline bool DivineData::has_firstkey() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void DivineData::set_has_firstkey() {
  _has_bits_[0] |= 0x00000010u;
}
inline void DivineData::clear_has_firstkey() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void DivineData::clear_firstkey() {
  firstkey_ = 0u;
  clear_has_firstkey();
}
inline ::google::protobuf::uint32 DivineData::firstkey() const {
  return firstkey_;
}
inline void DivineData::set_firstkey(::google::protobuf::uint32 value) {
  set_has_firstkey();
  firstkey_ = value;
}

// required .HelloKittyMsgData.DivineStatus status = 6;
inline bool DivineData::has_status() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void DivineData::set_has_status() {
  _has_bits_[0] |= 0x00000020u;
}
inline void DivineData::clear_has_status() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void DivineData::clear_status() {
  status_ = 0;
  clear_has_status();
}
inline ::HelloKittyMsgData::DivineStatus DivineData::status() const {
  return static_cast< ::HelloKittyMsgData::DivineStatus >(status_);
}
inline void DivineData::set_status(::HelloKittyMsgData::DivineStatus value) {
  assert(::HelloKittyMsgData::DivineStatus_IsValid(value));
  set_has_status();
  status_ = value;
}

// -------------------------------------------------------------------

// ReqDivineInfo

// -------------------------------------------------------------------

// ReqDivineNotice

// -------------------------------------------------------------------

// ReqDivine

// required bool notify = 1;
inline bool ReqDivine::has_notify() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ReqDivine::set_has_notify() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ReqDivine::clear_has_notify() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ReqDivine::clear_notify() {
  notify_ = false;
  clear_has_notify();
}
inline bool ReqDivine::notify() const {
  return notify_;
}
inline void ReqDivine::set_notify(bool value) {
  set_has_notify();
  notify_ = value;
}

// -------------------------------------------------------------------

// AckDivine

// required .HelloKittyMsgData.DivineData divine = 1;
inline bool AckDivine::has_divine() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AckDivine::set_has_divine() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AckDivine::clear_has_divine() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AckDivine::clear_divine() {
  if (divine_ != NULL) divine_->::HelloKittyMsgData::DivineData::Clear();
  clear_has_divine();
}
inline const ::HelloKittyMsgData::DivineData& AckDivine::divine() const {
  return divine_ != NULL ? *divine_ : *default_instance_->divine_;
}
inline ::HelloKittyMsgData::DivineData* AckDivine::mutable_divine() {
  set_has_divine();
  if (divine_ == NULL) divine_ = new ::HelloKittyMsgData::DivineData;
  return divine_;
}
inline ::HelloKittyMsgData::DivineData* AckDivine::release_divine() {
  clear_has_divine();
  ::HelloKittyMsgData::DivineData* temp = divine_;
  divine_ = NULL;
  return temp;
}
inline void AckDivine::set_allocated_divine(::HelloKittyMsgData::DivineData* divine) {
  delete divine_;
  divine_ = divine;
  if (divine) {
    set_has_divine();
  } else {
    clear_has_divine();
  }
}

// -------------------------------------------------------------------

// ReqDivineVerify

// required string older = 1;
inline bool ReqDivineVerify::has_older() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ReqDivineVerify::set_has_older() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ReqDivineVerify::clear_has_older() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ReqDivineVerify::clear_older() {
  if (older_ != &::google::protobuf::internal::kEmptyString) {
    older_->clear();
  }
  clear_has_older();
}
inline const ::std::string& ReqDivineVerify::older() const {
  return *older_;
}
inline void ReqDivineVerify::set_older(const ::std::string& value) {
  set_has_older();
  if (older_ == &::google::protobuf::internal::kEmptyString) {
    older_ = new ::std::string;
  }
  older_->assign(value);
}
inline void ReqDivineVerify::set_older(const char* value) {
  set_has_older();
  if (older_ == &::google::protobuf::internal::kEmptyString) {
    older_ = new ::std::string;
  }
  older_->assign(value);
}
inline void ReqDivineVerify::set_older(const char* value, size_t size) {
  set_has_older();
  if (older_ == &::google::protobuf::internal::kEmptyString) {
    older_ = new ::std::string;
  }
  older_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ReqDivineVerify::mutable_older() {
  set_has_older();
  if (older_ == &::google::protobuf::internal::kEmptyString) {
    older_ = new ::std::string;
  }
  return older_;
}
inline ::std::string* ReqDivineVerify::release_older() {
  clear_has_older();
  if (older_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = older_;
    older_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void ReqDivineVerify::set_allocated_older(::std::string* older) {
  if (older_ != &::google::protobuf::internal::kEmptyString) {
    delete older_;
  }
  if (older) {
    set_has_older();
    older_ = older;
  } else {
    clear_has_older();
    older_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace HelloKittyMsgData

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::HelloKittyMsgData::DivineStatus>() {
  return ::HelloKittyMsgData::DivineStatus_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_divine_2eproto__INCLUDED
