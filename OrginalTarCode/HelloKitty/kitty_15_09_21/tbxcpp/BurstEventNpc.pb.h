// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: BurstEventNpc.proto

#ifndef PROTOBUF_BurstEventNpc_2eproto__INCLUDED
#define PROTOBUF_BurstEventNpc_2eproto__INCLUDED

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
void  protobuf_AddDesc_BurstEventNpc_2eproto();
void protobuf_AssignDesc_BurstEventNpc_2eproto();
void protobuf_ShutdownFile_BurstEventNpc_2eproto();

class BurstEventNpc;
class BurstEventNpc_t_BurstEventNpc;

// ===================================================================

class BurstEventNpc_t_BurstEventNpc : public ::google::protobuf::Message {
 public:
  BurstEventNpc_t_BurstEventNpc();
  virtual ~BurstEventNpc_t_BurstEventNpc();

  BurstEventNpc_t_BurstEventNpc(const BurstEventNpc_t_BurstEventNpc& from);

  inline BurstEventNpc_t_BurstEventNpc& operator=(const BurstEventNpc_t_BurstEventNpc& from) {
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
  static const BurstEventNpc_t_BurstEventNpc& default_instance();

  void Swap(BurstEventNpc_t_BurstEventNpc* other);

  // implements Message ----------------------------------------------

  BurstEventNpc_t_BurstEventNpc* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BurstEventNpc_t_BurstEventNpc& from);
  void MergeFrom(const BurstEventNpc_t_BurstEventNpc& from);
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

  // required uint32 npcid = 3;
  inline bool has_npcid() const;
  inline void clear_npcid();
  static const int kNpcidFieldNumber = 3;
  inline ::google::protobuf::uint32 npcid() const;
  inline void set_npcid(::google::protobuf::uint32 value);

  // required uint32 levelgrade = 4;
  inline bool has_levelgrade() const;
  inline void clear_levelgrade();
  static const int kLevelgradeFieldNumber = 4;
  inline ::google::protobuf::uint32 levelgrade() const;
  inline void set_levelgrade(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:pb.BurstEventNpc.t_BurstEventNpc)
 private:
  inline void set_has_tbxid();
  inline void clear_has_tbxid();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_npcid();
  inline void clear_has_npcid();
  inline void set_has_levelgrade();
  inline void clear_has_levelgrade();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 tbxid_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 npcid_;
  ::google::protobuf::uint32 levelgrade_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];

  friend void  protobuf_AddDesc_BurstEventNpc_2eproto();
  friend void protobuf_AssignDesc_BurstEventNpc_2eproto();
  friend void protobuf_ShutdownFile_BurstEventNpc_2eproto();

  void InitAsDefaultInstance();
  static BurstEventNpc_t_BurstEventNpc* default_instance_;
};
// -------------------------------------------------------------------

class BurstEventNpc : public ::google::protobuf::Message {
 public:
  BurstEventNpc();
  virtual ~BurstEventNpc();

  BurstEventNpc(const BurstEventNpc& from);

  inline BurstEventNpc& operator=(const BurstEventNpc& from) {
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
  static const BurstEventNpc& default_instance();

  void Swap(BurstEventNpc* other);

  // implements Message ----------------------------------------------

  BurstEventNpc* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BurstEventNpc& from);
  void MergeFrom(const BurstEventNpc& from);
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

  typedef BurstEventNpc_t_BurstEventNpc t_BurstEventNpc;

  // accessors -------------------------------------------------------

  // repeated .pb.BurstEventNpc.t_BurstEventNpc datas = 1;
  inline int datas_size() const;
  inline void clear_datas();
  static const int kDatasFieldNumber = 1;
  inline const ::pb::BurstEventNpc_t_BurstEventNpc& datas(int index) const;
  inline ::pb::BurstEventNpc_t_BurstEventNpc* mutable_datas(int index);
  inline ::pb::BurstEventNpc_t_BurstEventNpc* add_datas();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::BurstEventNpc_t_BurstEventNpc >&
      datas() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::BurstEventNpc_t_BurstEventNpc >*
      mutable_datas();

  // @@protoc_insertion_point(class_scope:pb.BurstEventNpc)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::pb::BurstEventNpc_t_BurstEventNpc > datas_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_BurstEventNpc_2eproto();
  friend void protobuf_AssignDesc_BurstEventNpc_2eproto();
  friend void protobuf_ShutdownFile_BurstEventNpc_2eproto();

  void InitAsDefaultInstance();
  static BurstEventNpc* default_instance_;
};
// ===================================================================


// ===================================================================

// BurstEventNpc_t_BurstEventNpc

// required uint32 tbxid = 1;
inline bool BurstEventNpc_t_BurstEventNpc::has_tbxid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BurstEventNpc_t_BurstEventNpc::set_has_tbxid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BurstEventNpc_t_BurstEventNpc::clear_has_tbxid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BurstEventNpc_t_BurstEventNpc::clear_tbxid() {
  tbxid_ = 0u;
  clear_has_tbxid();
}
inline ::google::protobuf::uint32 BurstEventNpc_t_BurstEventNpc::tbxid() const {
  return tbxid_;
}
inline void BurstEventNpc_t_BurstEventNpc::set_tbxid(::google::protobuf::uint32 value) {
  set_has_tbxid();
  tbxid_ = value;
}

// required uint32 id = 2;
inline bool BurstEventNpc_t_BurstEventNpc::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BurstEventNpc_t_BurstEventNpc::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BurstEventNpc_t_BurstEventNpc::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BurstEventNpc_t_BurstEventNpc::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 BurstEventNpc_t_BurstEventNpc::id() const {
  return id_;
}
inline void BurstEventNpc_t_BurstEventNpc::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required uint32 npcid = 3;
inline bool BurstEventNpc_t_BurstEventNpc::has_npcid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void BurstEventNpc_t_BurstEventNpc::set_has_npcid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void BurstEventNpc_t_BurstEventNpc::clear_has_npcid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void BurstEventNpc_t_BurstEventNpc::clear_npcid() {
  npcid_ = 0u;
  clear_has_npcid();
}
inline ::google::protobuf::uint32 BurstEventNpc_t_BurstEventNpc::npcid() const {
  return npcid_;
}
inline void BurstEventNpc_t_BurstEventNpc::set_npcid(::google::protobuf::uint32 value) {
  set_has_npcid();
  npcid_ = value;
}

// required uint32 levelgrade = 4;
inline bool BurstEventNpc_t_BurstEventNpc::has_levelgrade() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void BurstEventNpc_t_BurstEventNpc::set_has_levelgrade() {
  _has_bits_[0] |= 0x00000008u;
}
inline void BurstEventNpc_t_BurstEventNpc::clear_has_levelgrade() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void BurstEventNpc_t_BurstEventNpc::clear_levelgrade() {
  levelgrade_ = 0u;
  clear_has_levelgrade();
}
inline ::google::protobuf::uint32 BurstEventNpc_t_BurstEventNpc::levelgrade() const {
  return levelgrade_;
}
inline void BurstEventNpc_t_BurstEventNpc::set_levelgrade(::google::protobuf::uint32 value) {
  set_has_levelgrade();
  levelgrade_ = value;
}

// -------------------------------------------------------------------

// BurstEventNpc

// repeated .pb.BurstEventNpc.t_BurstEventNpc datas = 1;
inline int BurstEventNpc::datas_size() const {
  return datas_.size();
}
inline void BurstEventNpc::clear_datas() {
  datas_.Clear();
}
inline const ::pb::BurstEventNpc_t_BurstEventNpc& BurstEventNpc::datas(int index) const {
  return datas_.Get(index);
}
inline ::pb::BurstEventNpc_t_BurstEventNpc* BurstEventNpc::mutable_datas(int index) {
  return datas_.Mutable(index);
}
inline ::pb::BurstEventNpc_t_BurstEventNpc* BurstEventNpc::add_datas() {
  return datas_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::BurstEventNpc_t_BurstEventNpc >&
BurstEventNpc::datas() const {
  return datas_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::BurstEventNpc_t_BurstEventNpc >*
BurstEventNpc::mutable_datas() {
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

#endif  // PROTOBUF_BurstEventNpc_2eproto__INCLUDED
