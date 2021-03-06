// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CarnivalShop.proto

#ifndef PROTOBUF_CarnivalShop_2eproto__INCLUDED
#define PROTOBUF_CarnivalShop_2eproto__INCLUDED

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
void  protobuf_AddDesc_CarnivalShop_2eproto();
void protobuf_AssignDesc_CarnivalShop_2eproto();
void protobuf_ShutdownFile_CarnivalShop_2eproto();

class CarnivalShop;
class CarnivalShop_t_CarnivalShop;

// ===================================================================

class CarnivalShop_t_CarnivalShop : public ::google::protobuf::Message {
 public:
  CarnivalShop_t_CarnivalShop();
  virtual ~CarnivalShop_t_CarnivalShop();

  CarnivalShop_t_CarnivalShop(const CarnivalShop_t_CarnivalShop& from);

  inline CarnivalShop_t_CarnivalShop& operator=(const CarnivalShop_t_CarnivalShop& from) {
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
  static const CarnivalShop_t_CarnivalShop& default_instance();

  void Swap(CarnivalShop_t_CarnivalShop* other);

  // implements Message ----------------------------------------------

  CarnivalShop_t_CarnivalShop* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CarnivalShop_t_CarnivalShop& from);
  void MergeFrom(const CarnivalShop_t_CarnivalShop& from);
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

  // required string weight = 3;
  inline bool has_weight() const;
  inline void clear_weight();
  static const int kWeightFieldNumber = 3;
  inline const ::std::string& weight() const;
  inline void set_weight(const ::std::string& value);
  inline void set_weight(const char* value);
  inline void set_weight(const char* value, size_t size);
  inline ::std::string* mutable_weight();
  inline ::std::string* release_weight();
  inline void set_allocated_weight(::std::string* weight);

  // required uint32 discount = 4;
  inline bool has_discount() const;
  inline void clear_discount();
  static const int kDiscountFieldNumber = 4;
  inline ::google::protobuf::uint32 discount() const;
  inline void set_discount(::google::protobuf::uint32 value);

  // required uint32 lasttime = 5;
  inline bool has_lasttime() const;
  inline void clear_lasttime();
  static const int kLasttimeFieldNumber = 5;
  inline ::google::protobuf::uint32 lasttime() const;
  inline void set_lasttime(::google::protobuf::uint32 value);

  // required uint32 icon = 6;
  inline bool has_icon() const;
  inline void clear_icon();
  static const int kIconFieldNumber = 6;
  inline ::google::protobuf::uint32 icon() const;
  inline void set_icon(::google::protobuf::uint32 value);

  // required string point = 7;
  inline bool has_point() const;
  inline void clear_point();
  static const int kPointFieldNumber = 7;
  inline const ::std::string& point() const;
  inline void set_point(const ::std::string& value);
  inline void set_point(const char* value);
  inline void set_point(const char* value, size_t size);
  inline ::std::string* mutable_point();
  inline ::std::string* release_point();
  inline void set_allocated_point(::std::string* point);

  // @@protoc_insertion_point(class_scope:pb.CarnivalShop.t_CarnivalShop)
 private:
  inline void set_has_tbxid();
  inline void clear_has_tbxid();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_weight();
  inline void clear_has_weight();
  inline void set_has_discount();
  inline void clear_has_discount();
  inline void set_has_lasttime();
  inline void clear_has_lasttime();
  inline void set_has_icon();
  inline void clear_has_icon();
  inline void set_has_point();
  inline void clear_has_point();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 tbxid_;
  ::google::protobuf::uint32 id_;
  ::std::string* weight_;
  ::google::protobuf::uint32 discount_;
  ::google::protobuf::uint32 lasttime_;
  ::std::string* point_;
  ::google::protobuf::uint32 icon_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];

  friend void  protobuf_AddDesc_CarnivalShop_2eproto();
  friend void protobuf_AssignDesc_CarnivalShop_2eproto();
  friend void protobuf_ShutdownFile_CarnivalShop_2eproto();

  void InitAsDefaultInstance();
  static CarnivalShop_t_CarnivalShop* default_instance_;
};
// -------------------------------------------------------------------

class CarnivalShop : public ::google::protobuf::Message {
 public:
  CarnivalShop();
  virtual ~CarnivalShop();

  CarnivalShop(const CarnivalShop& from);

  inline CarnivalShop& operator=(const CarnivalShop& from) {
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
  static const CarnivalShop& default_instance();

  void Swap(CarnivalShop* other);

  // implements Message ----------------------------------------------

  CarnivalShop* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CarnivalShop& from);
  void MergeFrom(const CarnivalShop& from);
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

  typedef CarnivalShop_t_CarnivalShop t_CarnivalShop;

  // accessors -------------------------------------------------------

  // repeated .pb.CarnivalShop.t_CarnivalShop datas = 1;
  inline int datas_size() const;
  inline void clear_datas();
  static const int kDatasFieldNumber = 1;
  inline const ::pb::CarnivalShop_t_CarnivalShop& datas(int index) const;
  inline ::pb::CarnivalShop_t_CarnivalShop* mutable_datas(int index);
  inline ::pb::CarnivalShop_t_CarnivalShop* add_datas();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::CarnivalShop_t_CarnivalShop >&
      datas() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::CarnivalShop_t_CarnivalShop >*
      mutable_datas();

  // @@protoc_insertion_point(class_scope:pb.CarnivalShop)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::pb::CarnivalShop_t_CarnivalShop > datas_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_CarnivalShop_2eproto();
  friend void protobuf_AssignDesc_CarnivalShop_2eproto();
  friend void protobuf_ShutdownFile_CarnivalShop_2eproto();

  void InitAsDefaultInstance();
  static CarnivalShop* default_instance_;
};
// ===================================================================


// ===================================================================

// CarnivalShop_t_CarnivalShop

// required uint32 tbxid = 1;
inline bool CarnivalShop_t_CarnivalShop::has_tbxid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CarnivalShop_t_CarnivalShop::set_has_tbxid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CarnivalShop_t_CarnivalShop::clear_has_tbxid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CarnivalShop_t_CarnivalShop::clear_tbxid() {
  tbxid_ = 0u;
  clear_has_tbxid();
}
inline ::google::protobuf::uint32 CarnivalShop_t_CarnivalShop::tbxid() const {
  return tbxid_;
}
inline void CarnivalShop_t_CarnivalShop::set_tbxid(::google::protobuf::uint32 value) {
  set_has_tbxid();
  tbxid_ = value;
}

// required uint32 id = 2;
inline bool CarnivalShop_t_CarnivalShop::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CarnivalShop_t_CarnivalShop::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CarnivalShop_t_CarnivalShop::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CarnivalShop_t_CarnivalShop::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 CarnivalShop_t_CarnivalShop::id() const {
  return id_;
}
inline void CarnivalShop_t_CarnivalShop::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required string weight = 3;
inline bool CarnivalShop_t_CarnivalShop::has_weight() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void CarnivalShop_t_CarnivalShop::set_has_weight() {
  _has_bits_[0] |= 0x00000004u;
}
inline void CarnivalShop_t_CarnivalShop::clear_has_weight() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void CarnivalShop_t_CarnivalShop::clear_weight() {
  if (weight_ != &::google::protobuf::internal::kEmptyString) {
    weight_->clear();
  }
  clear_has_weight();
}
inline const ::std::string& CarnivalShop_t_CarnivalShop::weight() const {
  return *weight_;
}
inline void CarnivalShop_t_CarnivalShop::set_weight(const ::std::string& value) {
  set_has_weight();
  if (weight_ == &::google::protobuf::internal::kEmptyString) {
    weight_ = new ::std::string;
  }
  weight_->assign(value);
}
inline void CarnivalShop_t_CarnivalShop::set_weight(const char* value) {
  set_has_weight();
  if (weight_ == &::google::protobuf::internal::kEmptyString) {
    weight_ = new ::std::string;
  }
  weight_->assign(value);
}
inline void CarnivalShop_t_CarnivalShop::set_weight(const char* value, size_t size) {
  set_has_weight();
  if (weight_ == &::google::protobuf::internal::kEmptyString) {
    weight_ = new ::std::string;
  }
  weight_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* CarnivalShop_t_CarnivalShop::mutable_weight() {
  set_has_weight();
  if (weight_ == &::google::protobuf::internal::kEmptyString) {
    weight_ = new ::std::string;
  }
  return weight_;
}
inline ::std::string* CarnivalShop_t_CarnivalShop::release_weight() {
  clear_has_weight();
  if (weight_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = weight_;
    weight_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void CarnivalShop_t_CarnivalShop::set_allocated_weight(::std::string* weight) {
  if (weight_ != &::google::protobuf::internal::kEmptyString) {
    delete weight_;
  }
  if (weight) {
    set_has_weight();
    weight_ = weight;
  } else {
    clear_has_weight();
    weight_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required uint32 discount = 4;
inline bool CarnivalShop_t_CarnivalShop::has_discount() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void CarnivalShop_t_CarnivalShop::set_has_discount() {
  _has_bits_[0] |= 0x00000008u;
}
inline void CarnivalShop_t_CarnivalShop::clear_has_discount() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void CarnivalShop_t_CarnivalShop::clear_discount() {
  discount_ = 0u;
  clear_has_discount();
}
inline ::google::protobuf::uint32 CarnivalShop_t_CarnivalShop::discount() const {
  return discount_;
}
inline void CarnivalShop_t_CarnivalShop::set_discount(::google::protobuf::uint32 value) {
  set_has_discount();
  discount_ = value;
}

// required uint32 lasttime = 5;
inline bool CarnivalShop_t_CarnivalShop::has_lasttime() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void CarnivalShop_t_CarnivalShop::set_has_lasttime() {
  _has_bits_[0] |= 0x00000010u;
}
inline void CarnivalShop_t_CarnivalShop::clear_has_lasttime() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void CarnivalShop_t_CarnivalShop::clear_lasttime() {
  lasttime_ = 0u;
  clear_has_lasttime();
}
inline ::google::protobuf::uint32 CarnivalShop_t_CarnivalShop::lasttime() const {
  return lasttime_;
}
inline void CarnivalShop_t_CarnivalShop::set_lasttime(::google::protobuf::uint32 value) {
  set_has_lasttime();
  lasttime_ = value;
}

// required uint32 icon = 6;
inline bool CarnivalShop_t_CarnivalShop::has_icon() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void CarnivalShop_t_CarnivalShop::set_has_icon() {
  _has_bits_[0] |= 0x00000020u;
}
inline void CarnivalShop_t_CarnivalShop::clear_has_icon() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void CarnivalShop_t_CarnivalShop::clear_icon() {
  icon_ = 0u;
  clear_has_icon();
}
inline ::google::protobuf::uint32 CarnivalShop_t_CarnivalShop::icon() const {
  return icon_;
}
inline void CarnivalShop_t_CarnivalShop::set_icon(::google::protobuf::uint32 value) {
  set_has_icon();
  icon_ = value;
}

// required string point = 7;
inline bool CarnivalShop_t_CarnivalShop::has_point() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void CarnivalShop_t_CarnivalShop::set_has_point() {
  _has_bits_[0] |= 0x00000040u;
}
inline void CarnivalShop_t_CarnivalShop::clear_has_point() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void CarnivalShop_t_CarnivalShop::clear_point() {
  if (point_ != &::google::protobuf::internal::kEmptyString) {
    point_->clear();
  }
  clear_has_point();
}
inline const ::std::string& CarnivalShop_t_CarnivalShop::point() const {
  return *point_;
}
inline void CarnivalShop_t_CarnivalShop::set_point(const ::std::string& value) {
  set_has_point();
  if (point_ == &::google::protobuf::internal::kEmptyString) {
    point_ = new ::std::string;
  }
  point_->assign(value);
}
inline void CarnivalShop_t_CarnivalShop::set_point(const char* value) {
  set_has_point();
  if (point_ == &::google::protobuf::internal::kEmptyString) {
    point_ = new ::std::string;
  }
  point_->assign(value);
}
inline void CarnivalShop_t_CarnivalShop::set_point(const char* value, size_t size) {
  set_has_point();
  if (point_ == &::google::protobuf::internal::kEmptyString) {
    point_ = new ::std::string;
  }
  point_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* CarnivalShop_t_CarnivalShop::mutable_point() {
  set_has_point();
  if (point_ == &::google::protobuf::internal::kEmptyString) {
    point_ = new ::std::string;
  }
  return point_;
}
inline ::std::string* CarnivalShop_t_CarnivalShop::release_point() {
  clear_has_point();
  if (point_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = point_;
    point_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void CarnivalShop_t_CarnivalShop::set_allocated_point(::std::string* point) {
  if (point_ != &::google::protobuf::internal::kEmptyString) {
    delete point_;
  }
  if (point) {
    set_has_point();
    point_ = point;
  } else {
    clear_has_point();
    point_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// CarnivalShop

// repeated .pb.CarnivalShop.t_CarnivalShop datas = 1;
inline int CarnivalShop::datas_size() const {
  return datas_.size();
}
inline void CarnivalShop::clear_datas() {
  datas_.Clear();
}
inline const ::pb::CarnivalShop_t_CarnivalShop& CarnivalShop::datas(int index) const {
  return datas_.Get(index);
}
inline ::pb::CarnivalShop_t_CarnivalShop* CarnivalShop::mutable_datas(int index) {
  return datas_.Mutable(index);
}
inline ::pb::CarnivalShop_t_CarnivalShop* CarnivalShop::add_datas() {
  return datas_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::CarnivalShop_t_CarnivalShop >&
CarnivalShop::datas() const {
  return datas_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::CarnivalShop_t_CarnivalShop >*
CarnivalShop::mutable_datas() {
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

#endif  // PROTOBUF_CarnivalShop_2eproto__INCLUDED
