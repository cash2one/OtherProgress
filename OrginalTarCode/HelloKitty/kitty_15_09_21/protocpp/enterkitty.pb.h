// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: enterkitty.proto

#ifndef PROTOBUF_enterkitty_2eproto__INCLUDED
#define PROTOBUF_enterkitty_2eproto__INCLUDED

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
#include "trade.pb.h"
#include "kittygarden.pb.h"
#include "build.pb.h"
#include "common.pb.h"
#include "event.pb.h"
// @@protoc_insertion_point(includes)

namespace HelloKittyMsgData {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_enterkitty_2eproto();
void protobuf_AssignDesc_enterkitty_2eproto();
void protobuf_ShutdownFile_enterkitty_2eproto();

class EnterGardenInfo;
class ReqEnterGarden;
class AckEnterGarden;

// ===================================================================

class EnterGardenInfo : public ::google::protobuf::Message {
 public:
  EnterGardenInfo();
  virtual ~EnterGardenInfo();

  EnterGardenInfo(const EnterGardenInfo& from);

  inline EnterGardenInfo& operator=(const EnterGardenInfo& from) {
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
  static const EnterGardenInfo& default_instance();

  void Swap(EnterGardenInfo* other);

  // implements Message ----------------------------------------------

  EnterGardenInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const EnterGardenInfo& from);
  void MergeFrom(const EnterGardenInfo& from);
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

  // required uint64 charId = 1;
  inline bool has_charid() const;
  inline void clear_charid();
  static const int kCharIdFieldNumber = 1;
  inline ::google::protobuf::uint64 charid() const;
  inline void set_charid(::google::protobuf::uint64 value);

  // required string name = 2;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 2;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // required uint32 level = 3;
  inline bool has_level() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 3;
  inline ::google::protobuf::uint32 level() const;
  inline void set_level(::google::protobuf::uint32 value);

  // required uint64 exp = 4;
  inline bool has_exp() const;
  inline void clear_exp();
  static const int kExpFieldNumber = 4;
  inline ::google::protobuf::uint64 exp() const;
  inline void set_exp(::google::protobuf::uint64 value);

  // repeated .HelloKittyMsgData.BuildBase buildinfo = 5;
  inline int buildinfo_size() const;
  inline void clear_buildinfo();
  static const int kBuildinfoFieldNumber = 5;
  inline const ::HelloKittyMsgData::BuildBase& buildinfo(int index) const;
  inline ::HelloKittyMsgData::BuildBase* mutable_buildinfo(int index);
  inline ::HelloKittyMsgData::BuildBase* add_buildinfo();
  inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::BuildBase >&
      buildinfo() const;
  inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::BuildBase >*
      mutable_buildinfo();

  // required .HelloKittyMsgData.KittyGarden kittygarden = 6;
  inline bool has_kittygarden() const;
  inline void clear_kittygarden();
  static const int kKittygardenFieldNumber = 6;
  inline const ::HelloKittyMsgData::KittyGarden& kittygarden() const;
  inline ::HelloKittyMsgData::KittyGarden* mutable_kittygarden();
  inline ::HelloKittyMsgData::KittyGarden* release_kittygarden();
  inline void set_allocated_kittygarden(::HelloKittyMsgData::KittyGarden* kittygarden);

  // repeated .HelloKittyMsgData.RubbishData rubbish = 7;
  inline int rubbish_size() const;
  inline void clear_rubbish();
  static const int kRubbishFieldNumber = 7;
  inline const ::HelloKittyMsgData::RubbishData& rubbish(int index) const;
  inline ::HelloKittyMsgData::RubbishData* mutable_rubbish(int index);
  inline ::HelloKittyMsgData::RubbishData* add_rubbish();
  inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::RubbishData >&
      rubbish() const;
  inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::RubbishData >*
      mutable_rubbish();

  // required .HelloKittyMsgData.Evententer eventinit = 8;
  inline bool has_eventinit() const;
  inline void clear_eventinit();
  static const int kEventinitFieldNumber = 8;
  inline const ::HelloKittyMsgData::Evententer& eventinit() const;
  inline ::HelloKittyMsgData::Evententer* mutable_eventinit();
  inline ::HelloKittyMsgData::Evententer* release_eventinit();
  inline void set_allocated_eventinit(::HelloKittyMsgData::Evententer* eventinit);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.EnterGardenInfo)
 private:
  inline void set_has_charid();
  inline void clear_has_charid();
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_level();
  inline void clear_has_level();
  inline void set_has_exp();
  inline void clear_has_exp();
  inline void set_has_kittygarden();
  inline void clear_has_kittygarden();
  inline void set_has_eventinit();
  inline void clear_has_eventinit();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint64 charid_;
  ::std::string* name_;
  ::google::protobuf::uint64 exp_;
  ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::BuildBase > buildinfo_;
  ::HelloKittyMsgData::KittyGarden* kittygarden_;
  ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::RubbishData > rubbish_;
  ::HelloKittyMsgData::Evententer* eventinit_;
  ::google::protobuf::uint32 level_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(8 + 31) / 32];

  friend void  protobuf_AddDesc_enterkitty_2eproto();
  friend void protobuf_AssignDesc_enterkitty_2eproto();
  friend void protobuf_ShutdownFile_enterkitty_2eproto();

  void InitAsDefaultInstance();
  static EnterGardenInfo* default_instance_;
};
// -------------------------------------------------------------------

class ReqEnterGarden : public ::google::protobuf::Message {
 public:
  ReqEnterGarden();
  virtual ~ReqEnterGarden();

  ReqEnterGarden(const ReqEnterGarden& from);

  inline ReqEnterGarden& operator=(const ReqEnterGarden& from) {
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
  static const ReqEnterGarden& default_instance();

  void Swap(ReqEnterGarden* other);

  // implements Message ----------------------------------------------

  ReqEnterGarden* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ReqEnterGarden& from);
  void MergeFrom(const ReqEnterGarden& from);
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

  // required uint64 charid = 1;
  inline bool has_charid() const;
  inline void clear_charid();
  static const int kCharidFieldNumber = 1;
  inline ::google::protobuf::uint64 charid() const;
  inline void set_charid(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.ReqEnterGarden)
 private:
  inline void set_has_charid();
  inline void clear_has_charid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint64 charid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_enterkitty_2eproto();
  friend void protobuf_AssignDesc_enterkitty_2eproto();
  friend void protobuf_ShutdownFile_enterkitty_2eproto();

  void InitAsDefaultInstance();
  static ReqEnterGarden* default_instance_;
};
// -------------------------------------------------------------------

class AckEnterGarden : public ::google::protobuf::Message {
 public:
  AckEnterGarden();
  virtual ~AckEnterGarden();

  AckEnterGarden(const AckEnterGarden& from);

  inline AckEnterGarden& operator=(const AckEnterGarden& from) {
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
  static const AckEnterGarden& default_instance();

  void Swap(AckEnterGarden* other);

  // implements Message ----------------------------------------------

  AckEnterGarden* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AckEnterGarden& from);
  void MergeFrom(const AckEnterGarden& from);
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

  // required .HelloKittyMsgData.EnterGardenInfo gardenInfo = 1;
  inline bool has_gardeninfo() const;
  inline void clear_gardeninfo();
  static const int kGardenInfoFieldNumber = 1;
  inline const ::HelloKittyMsgData::EnterGardenInfo& gardeninfo() const;
  inline ::HelloKittyMsgData::EnterGardenInfo* mutable_gardeninfo();
  inline ::HelloKittyMsgData::EnterGardenInfo* release_gardeninfo();
  inline void set_allocated_gardeninfo(::HelloKittyMsgData::EnterGardenInfo* gardeninfo);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.AckEnterGarden)
 private:
  inline void set_has_gardeninfo();
  inline void clear_has_gardeninfo();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::HelloKittyMsgData::EnterGardenInfo* gardeninfo_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_enterkitty_2eproto();
  friend void protobuf_AssignDesc_enterkitty_2eproto();
  friend void protobuf_ShutdownFile_enterkitty_2eproto();

  void InitAsDefaultInstance();
  static AckEnterGarden* default_instance_;
};
// ===================================================================


// ===================================================================

// EnterGardenInfo

// required uint64 charId = 1;
inline bool EnterGardenInfo::has_charid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void EnterGardenInfo::set_has_charid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void EnterGardenInfo::clear_has_charid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void EnterGardenInfo::clear_charid() {
  charid_ = GOOGLE_ULONGLONG(0);
  clear_has_charid();
}
inline ::google::protobuf::uint64 EnterGardenInfo::charid() const {
  return charid_;
}
inline void EnterGardenInfo::set_charid(::google::protobuf::uint64 value) {
  set_has_charid();
  charid_ = value;
}

// required string name = 2;
inline bool EnterGardenInfo::has_name() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void EnterGardenInfo::set_has_name() {
  _has_bits_[0] |= 0x00000002u;
}
inline void EnterGardenInfo::clear_has_name() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void EnterGardenInfo::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& EnterGardenInfo::name() const {
  return *name_;
}
inline void EnterGardenInfo::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void EnterGardenInfo::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void EnterGardenInfo::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* EnterGardenInfo::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* EnterGardenInfo::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void EnterGardenInfo::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required uint32 level = 3;
inline bool EnterGardenInfo::has_level() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void EnterGardenInfo::set_has_level() {
  _has_bits_[0] |= 0x00000004u;
}
inline void EnterGardenInfo::clear_has_level() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void EnterGardenInfo::clear_level() {
  level_ = 0u;
  clear_has_level();
}
inline ::google::protobuf::uint32 EnterGardenInfo::level() const {
  return level_;
}
inline void EnterGardenInfo::set_level(::google::protobuf::uint32 value) {
  set_has_level();
  level_ = value;
}

// required uint64 exp = 4;
inline bool EnterGardenInfo::has_exp() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void EnterGardenInfo::set_has_exp() {
  _has_bits_[0] |= 0x00000008u;
}
inline void EnterGardenInfo::clear_has_exp() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void EnterGardenInfo::clear_exp() {
  exp_ = GOOGLE_ULONGLONG(0);
  clear_has_exp();
}
inline ::google::protobuf::uint64 EnterGardenInfo::exp() const {
  return exp_;
}
inline void EnterGardenInfo::set_exp(::google::protobuf::uint64 value) {
  set_has_exp();
  exp_ = value;
}

// repeated .HelloKittyMsgData.BuildBase buildinfo = 5;
inline int EnterGardenInfo::buildinfo_size() const {
  return buildinfo_.size();
}
inline void EnterGardenInfo::clear_buildinfo() {
  buildinfo_.Clear();
}
inline const ::HelloKittyMsgData::BuildBase& EnterGardenInfo::buildinfo(int index) const {
  return buildinfo_.Get(index);
}
inline ::HelloKittyMsgData::BuildBase* EnterGardenInfo::mutable_buildinfo(int index) {
  return buildinfo_.Mutable(index);
}
inline ::HelloKittyMsgData::BuildBase* EnterGardenInfo::add_buildinfo() {
  return buildinfo_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::BuildBase >&
EnterGardenInfo::buildinfo() const {
  return buildinfo_;
}
inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::BuildBase >*
EnterGardenInfo::mutable_buildinfo() {
  return &buildinfo_;
}

// required .HelloKittyMsgData.KittyGarden kittygarden = 6;
inline bool EnterGardenInfo::has_kittygarden() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void EnterGardenInfo::set_has_kittygarden() {
  _has_bits_[0] |= 0x00000020u;
}
inline void EnterGardenInfo::clear_has_kittygarden() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void EnterGardenInfo::clear_kittygarden() {
  if (kittygarden_ != NULL) kittygarden_->::HelloKittyMsgData::KittyGarden::Clear();
  clear_has_kittygarden();
}
inline const ::HelloKittyMsgData::KittyGarden& EnterGardenInfo::kittygarden() const {
  return kittygarden_ != NULL ? *kittygarden_ : *default_instance_->kittygarden_;
}
inline ::HelloKittyMsgData::KittyGarden* EnterGardenInfo::mutable_kittygarden() {
  set_has_kittygarden();
  if (kittygarden_ == NULL) kittygarden_ = new ::HelloKittyMsgData::KittyGarden;
  return kittygarden_;
}
inline ::HelloKittyMsgData::KittyGarden* EnterGardenInfo::release_kittygarden() {
  clear_has_kittygarden();
  ::HelloKittyMsgData::KittyGarden* temp = kittygarden_;
  kittygarden_ = NULL;
  return temp;
}
inline void EnterGardenInfo::set_allocated_kittygarden(::HelloKittyMsgData::KittyGarden* kittygarden) {
  delete kittygarden_;
  kittygarden_ = kittygarden;
  if (kittygarden) {
    set_has_kittygarden();
  } else {
    clear_has_kittygarden();
  }
}

// repeated .HelloKittyMsgData.RubbishData rubbish = 7;
inline int EnterGardenInfo::rubbish_size() const {
  return rubbish_.size();
}
inline void EnterGardenInfo::clear_rubbish() {
  rubbish_.Clear();
}
inline const ::HelloKittyMsgData::RubbishData& EnterGardenInfo::rubbish(int index) const {
  return rubbish_.Get(index);
}
inline ::HelloKittyMsgData::RubbishData* EnterGardenInfo::mutable_rubbish(int index) {
  return rubbish_.Mutable(index);
}
inline ::HelloKittyMsgData::RubbishData* EnterGardenInfo::add_rubbish() {
  return rubbish_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::RubbishData >&
EnterGardenInfo::rubbish() const {
  return rubbish_;
}
inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::RubbishData >*
EnterGardenInfo::mutable_rubbish() {
  return &rubbish_;
}

// required .HelloKittyMsgData.Evententer eventinit = 8;
inline bool EnterGardenInfo::has_eventinit() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void EnterGardenInfo::set_has_eventinit() {
  _has_bits_[0] |= 0x00000080u;
}
inline void EnterGardenInfo::clear_has_eventinit() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void EnterGardenInfo::clear_eventinit() {
  if (eventinit_ != NULL) eventinit_->::HelloKittyMsgData::Evententer::Clear();
  clear_has_eventinit();
}
inline const ::HelloKittyMsgData::Evententer& EnterGardenInfo::eventinit() const {
  return eventinit_ != NULL ? *eventinit_ : *default_instance_->eventinit_;
}
inline ::HelloKittyMsgData::Evententer* EnterGardenInfo::mutable_eventinit() {
  set_has_eventinit();
  if (eventinit_ == NULL) eventinit_ = new ::HelloKittyMsgData::Evententer;
  return eventinit_;
}
inline ::HelloKittyMsgData::Evententer* EnterGardenInfo::release_eventinit() {
  clear_has_eventinit();
  ::HelloKittyMsgData::Evententer* temp = eventinit_;
  eventinit_ = NULL;
  return temp;
}
inline void EnterGardenInfo::set_allocated_eventinit(::HelloKittyMsgData::Evententer* eventinit) {
  delete eventinit_;
  eventinit_ = eventinit;
  if (eventinit) {
    set_has_eventinit();
  } else {
    clear_has_eventinit();
  }
}

// -------------------------------------------------------------------

// ReqEnterGarden

// required uint64 charid = 1;
inline bool ReqEnterGarden::has_charid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ReqEnterGarden::set_has_charid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ReqEnterGarden::clear_has_charid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ReqEnterGarden::clear_charid() {
  charid_ = GOOGLE_ULONGLONG(0);
  clear_has_charid();
}
inline ::google::protobuf::uint64 ReqEnterGarden::charid() const {
  return charid_;
}
inline void ReqEnterGarden::set_charid(::google::protobuf::uint64 value) {
  set_has_charid();
  charid_ = value;
}

// -------------------------------------------------------------------

// AckEnterGarden

// required .HelloKittyMsgData.EnterGardenInfo gardenInfo = 1;
inline bool AckEnterGarden::has_gardeninfo() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AckEnterGarden::set_has_gardeninfo() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AckEnterGarden::clear_has_gardeninfo() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AckEnterGarden::clear_gardeninfo() {
  if (gardeninfo_ != NULL) gardeninfo_->::HelloKittyMsgData::EnterGardenInfo::Clear();
  clear_has_gardeninfo();
}
inline const ::HelloKittyMsgData::EnterGardenInfo& AckEnterGarden::gardeninfo() const {
  return gardeninfo_ != NULL ? *gardeninfo_ : *default_instance_->gardeninfo_;
}
inline ::HelloKittyMsgData::EnterGardenInfo* AckEnterGarden::mutable_gardeninfo() {
  set_has_gardeninfo();
  if (gardeninfo_ == NULL) gardeninfo_ = new ::HelloKittyMsgData::EnterGardenInfo;
  return gardeninfo_;
}
inline ::HelloKittyMsgData::EnterGardenInfo* AckEnterGarden::release_gardeninfo() {
  clear_has_gardeninfo();
  ::HelloKittyMsgData::EnterGardenInfo* temp = gardeninfo_;
  gardeninfo_ = NULL;
  return temp;
}
inline void AckEnterGarden::set_allocated_gardeninfo(::HelloKittyMsgData::EnterGardenInfo* gardeninfo) {
  delete gardeninfo_;
  gardeninfo_ = gardeninfo;
  if (gardeninfo) {
    set_has_gardeninfo();
  } else {
    clear_has_gardeninfo();
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace HelloKittyMsgData

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_enterkitty_2eproto__INCLUDED
