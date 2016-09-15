// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Role.proto

#ifndef PROTOBUF_Role_2eproto__INCLUDED
#define PROTOBUF_Role_2eproto__INCLUDED

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
void  protobuf_AddDesc_Role_2eproto();
void protobuf_AssignDesc_Role_2eproto();
void protobuf_ShutdownFile_Role_2eproto();

class upgrade;
class upgrade_t_upgrade;

// ===================================================================

class upgrade_t_upgrade : public ::google::protobuf::Message {
 public:
  upgrade_t_upgrade();
  virtual ~upgrade_t_upgrade();

  upgrade_t_upgrade(const upgrade_t_upgrade& from);

  inline upgrade_t_upgrade& operator=(const upgrade_t_upgrade& from) {
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
  static const upgrade_t_upgrade& default_instance();

  void Swap(upgrade_t_upgrade* other);

  // implements Message ----------------------------------------------

  upgrade_t_upgrade* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const upgrade_t_upgrade& from);
  void MergeFrom(const upgrade_t_upgrade& from);
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

  // required uint32 level = 3;
  inline bool has_level() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 3;
  inline ::google::protobuf::uint32 level() const;
  inline void set_level(::google::protobuf::uint32 value);

  // required uint32 exp = 4;
  inline bool has_exp() const;
  inline void clear_exp();
  static const int kExpFieldNumber = 4;
  inline ::google::protobuf::uint32 exp() const;
  inline void set_exp(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:pb.upgrade.t_upgrade)
 private:
  inline void set_has_tbxid();
  inline void clear_has_tbxid();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_level();
  inline void clear_has_level();
  inline void set_has_exp();
  inline void clear_has_exp();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 tbxid_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 level_;
  ::google::protobuf::uint32 exp_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];

  friend void  protobuf_AddDesc_Role_2eproto();
  friend void protobuf_AssignDesc_Role_2eproto();
  friend void protobuf_ShutdownFile_Role_2eproto();

  void InitAsDefaultInstance();
  static upgrade_t_upgrade* default_instance_;
};
// -------------------------------------------------------------------

class upgrade : public ::google::protobuf::Message {
 public:
  upgrade();
  virtual ~upgrade();

  upgrade(const upgrade& from);

  inline upgrade& operator=(const upgrade& from) {
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
  static const upgrade& default_instance();

  void Swap(upgrade* other);

  // implements Message ----------------------------------------------

  upgrade* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const upgrade& from);
  void MergeFrom(const upgrade& from);
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

  typedef upgrade_t_upgrade t_upgrade;

  // accessors -------------------------------------------------------

  // repeated .pb.upgrade.t_upgrade datas = 1;
  inline int datas_size() const;
  inline void clear_datas();
  static const int kDatasFieldNumber = 1;
  inline const ::pb::upgrade_t_upgrade& datas(int index) const;
  inline ::pb::upgrade_t_upgrade* mutable_datas(int index);
  inline ::pb::upgrade_t_upgrade* add_datas();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::upgrade_t_upgrade >&
      datas() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::upgrade_t_upgrade >*
      mutable_datas();

  // @@protoc_insertion_point(class_scope:pb.upgrade)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::pb::upgrade_t_upgrade > datas_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_Role_2eproto();
  friend void protobuf_AssignDesc_Role_2eproto();
  friend void protobuf_ShutdownFile_Role_2eproto();

  void InitAsDefaultInstance();
  static upgrade* default_instance_;
};
// ===================================================================


// ===================================================================

// upgrade_t_upgrade

// required uint32 tbxid = 1;
inline bool upgrade_t_upgrade::has_tbxid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void upgrade_t_upgrade::set_has_tbxid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void upgrade_t_upgrade::clear_has_tbxid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void upgrade_t_upgrade::clear_tbxid() {
  tbxid_ = 0u;
  clear_has_tbxid();
}
inline ::google::protobuf::uint32 upgrade_t_upgrade::tbxid() const {
  return tbxid_;
}
inline void upgrade_t_upgrade::set_tbxid(::google::protobuf::uint32 value) {
  set_has_tbxid();
  tbxid_ = value;
}

// required uint32 id = 2;
inline bool upgrade_t_upgrade::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void upgrade_t_upgrade::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void upgrade_t_upgrade::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void upgrade_t_upgrade::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 upgrade_t_upgrade::id() const {
  return id_;
}
inline void upgrade_t_upgrade::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required uint32 level = 3;
inline bool upgrade_t_upgrade::has_level() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void upgrade_t_upgrade::set_has_level() {
  _has_bits_[0] |= 0x00000004u;
}
inline void upgrade_t_upgrade::clear_has_level() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void upgrade_t_upgrade::clear_level() {
  level_ = 0u;
  clear_has_level();
}
inline ::google::protobuf::uint32 upgrade_t_upgrade::level() const {
  return level_;
}
inline void upgrade_t_upgrade::set_level(::google::protobuf::uint32 value) {
  set_has_level();
  level_ = value;
}

// required uint32 exp = 4;
inline bool upgrade_t_upgrade::has_exp() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void upgrade_t_upgrade::set_has_exp() {
  _has_bits_[0] |= 0x00000008u;
}
inline void upgrade_t_upgrade::clear_has_exp() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void upgrade_t_upgrade::clear_exp() {
  exp_ = 0u;
  clear_has_exp();
}
inline ::google::protobuf::uint32 upgrade_t_upgrade::exp() const {
  return exp_;
}
inline void upgrade_t_upgrade::set_exp(::google::protobuf::uint32 value) {
  set_has_exp();
  exp_ = value;
}

// -------------------------------------------------------------------

// upgrade

// repeated .pb.upgrade.t_upgrade datas = 1;
inline int upgrade::datas_size() const {
  return datas_.size();
}
inline void upgrade::clear_datas() {
  datas_.Clear();
}
inline const ::pb::upgrade_t_upgrade& upgrade::datas(int index) const {
  return datas_.Get(index);
}
inline ::pb::upgrade_t_upgrade* upgrade::mutable_datas(int index) {
  return datas_.Mutable(index);
}
inline ::pb::upgrade_t_upgrade* upgrade::add_datas() {
  return datas_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::upgrade_t_upgrade >&
upgrade::datas() const {
  return datas_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::upgrade_t_upgrade >*
upgrade::mutable_datas() {
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

#endif  // PROTOBUF_Role_2eproto__INCLUDED