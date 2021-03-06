// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ShopType.proto

#ifndef PROTOBUF_ShopType_2eproto__INCLUDED
#define PROTOBUF_ShopType_2eproto__INCLUDED

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
void  protobuf_AddDesc_ShopType_2eproto();
void protobuf_AssignDesc_ShopType_2eproto();
void protobuf_ShutdownFile_ShopType_2eproto();

class ShopType;
class ShopType_t_ShopType;

// ===================================================================

class ShopType_t_ShopType : public ::google::protobuf::Message {
 public:
  ShopType_t_ShopType();
  virtual ~ShopType_t_ShopType();

  ShopType_t_ShopType(const ShopType_t_ShopType& from);

  inline ShopType_t_ShopType& operator=(const ShopType_t_ShopType& from) {
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
  static const ShopType_t_ShopType& default_instance();

  void Swap(ShopType_t_ShopType* other);

  // implements Message ----------------------------------------------

  ShopType_t_ShopType* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ShopType_t_ShopType& from);
  void MergeFrom(const ShopType_t_ShopType& from);
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

  // required uint32 order = 3;
  inline bool has_order() const;
  inline void clear_order();
  static const int kOrderFieldNumber = 3;
  inline ::google::protobuf::uint32 order() const;
  inline void set_order(::google::protobuf::uint32 value);

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

  // required string name = 5;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 5;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // required uint32 open = 6;
  inline bool has_open() const;
  inline void clear_open();
  static const int kOpenFieldNumber = 6;
  inline ::google::protobuf::uint32 open() const;
  inline void set_open(::google::protobuf::uint32 value);

  // required uint32 minLevel = 7;
  inline bool has_minlevel() const;
  inline void clear_minlevel();
  static const int kMinLevelFieldNumber = 7;
  inline ::google::protobuf::uint32 minlevel() const;
  inline void set_minlevel(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:pb.ShopType.t_ShopType)
 private:
  inline void set_has_tbxid();
  inline void clear_has_tbxid();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_order();
  inline void clear_has_order();
  inline void set_has_icon();
  inline void clear_has_icon();
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_open();
  inline void clear_has_open();
  inline void set_has_minlevel();
  inline void clear_has_minlevel();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 tbxid_;
  ::google::protobuf::uint32 id_;
  ::std::string* icon_;
  ::google::protobuf::uint32 order_;
  ::google::protobuf::uint32 open_;
  ::std::string* name_;
  ::google::protobuf::uint32 minlevel_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];

  friend void  protobuf_AddDesc_ShopType_2eproto();
  friend void protobuf_AssignDesc_ShopType_2eproto();
  friend void protobuf_ShutdownFile_ShopType_2eproto();

  void InitAsDefaultInstance();
  static ShopType_t_ShopType* default_instance_;
};
// -------------------------------------------------------------------

class ShopType : public ::google::protobuf::Message {
 public:
  ShopType();
  virtual ~ShopType();

  ShopType(const ShopType& from);

  inline ShopType& operator=(const ShopType& from) {
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
  static const ShopType& default_instance();

  void Swap(ShopType* other);

  // implements Message ----------------------------------------------

  ShopType* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ShopType& from);
  void MergeFrom(const ShopType& from);
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

  typedef ShopType_t_ShopType t_ShopType;

  // accessors -------------------------------------------------------

  // repeated .pb.ShopType.t_ShopType datas = 1;
  inline int datas_size() const;
  inline void clear_datas();
  static const int kDatasFieldNumber = 1;
  inline const ::pb::ShopType_t_ShopType& datas(int index) const;
  inline ::pb::ShopType_t_ShopType* mutable_datas(int index);
  inline ::pb::ShopType_t_ShopType* add_datas();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::ShopType_t_ShopType >&
      datas() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::ShopType_t_ShopType >*
      mutable_datas();

  // @@protoc_insertion_point(class_scope:pb.ShopType)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::pb::ShopType_t_ShopType > datas_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_ShopType_2eproto();
  friend void protobuf_AssignDesc_ShopType_2eproto();
  friend void protobuf_ShutdownFile_ShopType_2eproto();

  void InitAsDefaultInstance();
  static ShopType* default_instance_;
};
// ===================================================================


// ===================================================================

// ShopType_t_ShopType

// required uint32 tbxid = 1;
inline bool ShopType_t_ShopType::has_tbxid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ShopType_t_ShopType::set_has_tbxid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ShopType_t_ShopType::clear_has_tbxid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ShopType_t_ShopType::clear_tbxid() {
  tbxid_ = 0u;
  clear_has_tbxid();
}
inline ::google::protobuf::uint32 ShopType_t_ShopType::tbxid() const {
  return tbxid_;
}
inline void ShopType_t_ShopType::set_tbxid(::google::protobuf::uint32 value) {
  set_has_tbxid();
  tbxid_ = value;
}

// required uint32 id = 2;
inline bool ShopType_t_ShopType::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ShopType_t_ShopType::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ShopType_t_ShopType::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ShopType_t_ShopType::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 ShopType_t_ShopType::id() const {
  return id_;
}
inline void ShopType_t_ShopType::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required uint32 order = 3;
inline bool ShopType_t_ShopType::has_order() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ShopType_t_ShopType::set_has_order() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ShopType_t_ShopType::clear_has_order() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ShopType_t_ShopType::clear_order() {
  order_ = 0u;
  clear_has_order();
}
inline ::google::protobuf::uint32 ShopType_t_ShopType::order() const {
  return order_;
}
inline void ShopType_t_ShopType::set_order(::google::protobuf::uint32 value) {
  set_has_order();
  order_ = value;
}

// required string icon = 4;
inline bool ShopType_t_ShopType::has_icon() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ShopType_t_ShopType::set_has_icon() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ShopType_t_ShopType::clear_has_icon() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ShopType_t_ShopType::clear_icon() {
  if (icon_ != &::google::protobuf::internal::kEmptyString) {
    icon_->clear();
  }
  clear_has_icon();
}
inline const ::std::string& ShopType_t_ShopType::icon() const {
  return *icon_;
}
inline void ShopType_t_ShopType::set_icon(const ::std::string& value) {
  set_has_icon();
  if (icon_ == &::google::protobuf::internal::kEmptyString) {
    icon_ = new ::std::string;
  }
  icon_->assign(value);
}
inline void ShopType_t_ShopType::set_icon(const char* value) {
  set_has_icon();
  if (icon_ == &::google::protobuf::internal::kEmptyString) {
    icon_ = new ::std::string;
  }
  icon_->assign(value);
}
inline void ShopType_t_ShopType::set_icon(const char* value, size_t size) {
  set_has_icon();
  if (icon_ == &::google::protobuf::internal::kEmptyString) {
    icon_ = new ::std::string;
  }
  icon_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ShopType_t_ShopType::mutable_icon() {
  set_has_icon();
  if (icon_ == &::google::protobuf::internal::kEmptyString) {
    icon_ = new ::std::string;
  }
  return icon_;
}
inline ::std::string* ShopType_t_ShopType::release_icon() {
  clear_has_icon();
  if (icon_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = icon_;
    icon_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void ShopType_t_ShopType::set_allocated_icon(::std::string* icon) {
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

// required string name = 5;
inline bool ShopType_t_ShopType::has_name() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void ShopType_t_ShopType::set_has_name() {
  _has_bits_[0] |= 0x00000010u;
}
inline void ShopType_t_ShopType::clear_has_name() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void ShopType_t_ShopType::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& ShopType_t_ShopType::name() const {
  return *name_;
}
inline void ShopType_t_ShopType::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void ShopType_t_ShopType::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void ShopType_t_ShopType::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ShopType_t_ShopType::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* ShopType_t_ShopType::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void ShopType_t_ShopType::set_allocated_name(::std::string* name) {
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

// required uint32 open = 6;
inline bool ShopType_t_ShopType::has_open() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void ShopType_t_ShopType::set_has_open() {
  _has_bits_[0] |= 0x00000020u;
}
inline void ShopType_t_ShopType::clear_has_open() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void ShopType_t_ShopType::clear_open() {
  open_ = 0u;
  clear_has_open();
}
inline ::google::protobuf::uint32 ShopType_t_ShopType::open() const {
  return open_;
}
inline void ShopType_t_ShopType::set_open(::google::protobuf::uint32 value) {
  set_has_open();
  open_ = value;
}

// required uint32 minLevel = 7;
inline bool ShopType_t_ShopType::has_minlevel() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void ShopType_t_ShopType::set_has_minlevel() {
  _has_bits_[0] |= 0x00000040u;
}
inline void ShopType_t_ShopType::clear_has_minlevel() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void ShopType_t_ShopType::clear_minlevel() {
  minlevel_ = 0u;
  clear_has_minlevel();
}
inline ::google::protobuf::uint32 ShopType_t_ShopType::minlevel() const {
  return minlevel_;
}
inline void ShopType_t_ShopType::set_minlevel(::google::protobuf::uint32 value) {
  set_has_minlevel();
  minlevel_ = value;
}

// -------------------------------------------------------------------

// ShopType

// repeated .pb.ShopType.t_ShopType datas = 1;
inline int ShopType::datas_size() const {
  return datas_.size();
}
inline void ShopType::clear_datas() {
  datas_.Clear();
}
inline const ::pb::ShopType_t_ShopType& ShopType::datas(int index) const {
  return datas_.Get(index);
}
inline ::pb::ShopType_t_ShopType* ShopType::mutable_datas(int index) {
  return datas_.Mutable(index);
}
inline ::pb::ShopType_t_ShopType* ShopType::add_datas() {
  return datas_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::ShopType_t_ShopType >&
ShopType::datas() const {
  return datas_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::ShopType_t_ShopType >*
ShopType::mutable_datas() {
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

#endif  // PROTOBUF_ShopType_2eproto__INCLUDED
