// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: buildOption.proto

#ifndef PROTOBUF_buildOption_2eproto__INCLUDED
#define PROTOBUF_buildOption_2eproto__INCLUDED

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
void  protobuf_AddDesc_buildOption_2eproto();
void protobuf_AssignDesc_buildOption_2eproto();
void protobuf_ShutdownFile_buildOption_2eproto();

class buildOption;
class buildOption_t_buildOption;

// ===================================================================

class buildOption_t_buildOption : public ::google::protobuf::Message {
 public:
  buildOption_t_buildOption();
  virtual ~buildOption_t_buildOption();

  buildOption_t_buildOption(const buildOption_t_buildOption& from);

  inline buildOption_t_buildOption& operator=(const buildOption_t_buildOption& from) {
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
  static const buildOption_t_buildOption& default_instance();

  void Swap(buildOption_t_buildOption* other);

  // implements Message ----------------------------------------------

  buildOption_t_buildOption* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const buildOption_t_buildOption& from);
  void MergeFrom(const buildOption_t_buildOption& from);
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

  // required string name = 3;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 3;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // required string icon = 4;
  inline bool has_icon() const;
  inline void clear_icon();
  static const int kIconFieldNumber = 4;
  inline const ::std::string& icon() const;
  inline void set_icon(const ::std::string& value);
  inline void set_icon(const char* value);
  inline void set_icon(const char* value, size_t size);
  inline ::std::string* mutable_icon();
  inline ::std::string* release_icon();
  inline void set_allocated_icon(::std::string* icon);

  // @@protoc_insertion_point(class_scope:pb.buildOption.t_buildOption)
 private:
  inline void set_has_tbxid();
  inline void clear_has_tbxid();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_icon();
  inline void clear_has_icon();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 tbxid_;
  ::google::protobuf::uint32 id_;
  ::std::string* name_;
  ::std::string* icon_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];

  friend void  protobuf_AddDesc_buildOption_2eproto();
  friend void protobuf_AssignDesc_buildOption_2eproto();
  friend void protobuf_ShutdownFile_buildOption_2eproto();

  void InitAsDefaultInstance();
  static buildOption_t_buildOption* default_instance_;
};
// -------------------------------------------------------------------

class buildOption : public ::google::protobuf::Message {
 public:
  buildOption();
  virtual ~buildOption();

  buildOption(const buildOption& from);

  inline buildOption& operator=(const buildOption& from) {
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
  static const buildOption& default_instance();

  void Swap(buildOption* other);

  // implements Message ----------------------------------------------

  buildOption* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const buildOption& from);
  void MergeFrom(const buildOption& from);
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

  typedef buildOption_t_buildOption t_buildOption;

  // accessors -------------------------------------------------------

  // repeated .pb.buildOption.t_buildOption datas = 1;
  inline int datas_size() const;
  inline void clear_datas();
  static const int kDatasFieldNumber = 1;
  inline const ::pb::buildOption_t_buildOption& datas(int index) const;
  inline ::pb::buildOption_t_buildOption* mutable_datas(int index);
  inline ::pb::buildOption_t_buildOption* add_datas();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::buildOption_t_buildOption >&
      datas() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::buildOption_t_buildOption >*
      mutable_datas();

  // @@protoc_insertion_point(class_scope:pb.buildOption)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::pb::buildOption_t_buildOption > datas_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_buildOption_2eproto();
  friend void protobuf_AssignDesc_buildOption_2eproto();
  friend void protobuf_ShutdownFile_buildOption_2eproto();

  void InitAsDefaultInstance();
  static buildOption* default_instance_;
};
// ===================================================================


// ===================================================================

// buildOption_t_buildOption

// required uint32 tbxid = 1;
inline bool buildOption_t_buildOption::has_tbxid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void buildOption_t_buildOption::set_has_tbxid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void buildOption_t_buildOption::clear_has_tbxid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void buildOption_t_buildOption::clear_tbxid() {
  tbxid_ = 0u;
  clear_has_tbxid();
}
inline ::google::protobuf::uint32 buildOption_t_buildOption::tbxid() const {
  return tbxid_;
}
inline void buildOption_t_buildOption::set_tbxid(::google::protobuf::uint32 value) {
  set_has_tbxid();
  tbxid_ = value;
}

// required uint32 id = 2;
inline bool buildOption_t_buildOption::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void buildOption_t_buildOption::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void buildOption_t_buildOption::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void buildOption_t_buildOption::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 buildOption_t_buildOption::id() const {
  return id_;
}
inline void buildOption_t_buildOption::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required string name = 3;
inline bool buildOption_t_buildOption::has_name() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void buildOption_t_buildOption::set_has_name() {
  _has_bits_[0] |= 0x00000004u;
}
inline void buildOption_t_buildOption::clear_has_name() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void buildOption_t_buildOption::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& buildOption_t_buildOption::name() const {
  return *name_;
}
inline void buildOption_t_buildOption::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void buildOption_t_buildOption::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void buildOption_t_buildOption::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* buildOption_t_buildOption::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* buildOption_t_buildOption::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void buildOption_t_buildOption::set_allocated_name(::std::string* name) {
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

// required string icon = 4;
inline bool buildOption_t_buildOption::has_icon() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void buildOption_t_buildOption::set_has_icon() {
  _has_bits_[0] |= 0x00000008u;
}
inline void buildOption_t_buildOption::clear_has_icon() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void buildOption_t_buildOption::clear_icon() {
  if (icon_ != &::google::protobuf::internal::kEmptyString) {
    icon_->clear();
  }
  clear_has_icon();
}
inline const ::std::string& buildOption_t_buildOption::icon() const {
  return *icon_;
}
inline void buildOption_t_buildOption::set_icon(const ::std::string& value) {
  set_has_icon();
  if (icon_ == &::google::protobuf::internal::kEmptyString) {
    icon_ = new ::std::string;
  }
  icon_->assign(value);
}
inline void buildOption_t_buildOption::set_icon(const char* value) {
  set_has_icon();
  if (icon_ == &::google::protobuf::internal::kEmptyString) {
    icon_ = new ::std::string;
  }
  icon_->assign(value);
}
inline void buildOption_t_buildOption::set_icon(const char* value, size_t size) {
  set_has_icon();
  if (icon_ == &::google::protobuf::internal::kEmptyString) {
    icon_ = new ::std::string;
  }
  icon_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* buildOption_t_buildOption::mutable_icon() {
  set_has_icon();
  if (icon_ == &::google::protobuf::internal::kEmptyString) {
    icon_ = new ::std::string;
  }
  return icon_;
}
inline ::std::string* buildOption_t_buildOption::release_icon() {
  clear_has_icon();
  if (icon_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = icon_;
    icon_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void buildOption_t_buildOption::set_allocated_icon(::std::string* icon) {
  if (icon_ != &::google::protobuf::internal::kEmptyString) {
    delete icon_;
  }
  if (icon) {
    set_has_icon();
    icon_ = icon;
  } else {
    clear_has_icon();
    icon_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// buildOption

// repeated .pb.buildOption.t_buildOption datas = 1;
inline int buildOption::datas_size() const {
  return datas_.size();
}
inline void buildOption::clear_datas() {
  datas_.Clear();
}
inline const ::pb::buildOption_t_buildOption& buildOption::datas(int index) const {
  return datas_.Get(index);
}
inline ::pb::buildOption_t_buildOption* buildOption::mutable_datas(int index) {
  return datas_.Mutable(index);
}
inline ::pb::buildOption_t_buildOption* buildOption::add_datas() {
  return datas_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::buildOption_t_buildOption >&
buildOption::datas() const {
  return datas_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::buildOption_t_buildOption >*
buildOption::mutable_datas() {
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

#endif  // PROTOBUF_buildOption_2eproto__INCLUDED
