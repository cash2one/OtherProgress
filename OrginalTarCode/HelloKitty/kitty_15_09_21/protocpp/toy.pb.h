// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: toy.proto

#ifndef PROTOBUF_toy_2eproto__INCLUDED
#define PROTOBUF_toy_2eproto__INCLUDED

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
void  protobuf_AddDesc_toy_2eproto();
void protobuf_AssignDesc_toy_2eproto();
void protobuf_ShutdownFile_toy_2eproto();

class ReqOpToy;
class AckToy;
class AckRandToy;

enum OpToyType {
  OTT_Req = 0,
  OTT_Rand = 1
};
bool OpToyType_IsValid(int value);
const OpToyType OpToyType_MIN = OTT_Req;
const OpToyType OpToyType_MAX = OTT_Rand;
const int OpToyType_ARRAYSIZE = OpToyType_MAX + 1;

const ::google::protobuf::EnumDescriptor* OpToyType_descriptor();
inline const ::std::string& OpToyType_Name(OpToyType value) {
  return ::google::protobuf::internal::NameOfEnum(
    OpToyType_descriptor(), value);
}
inline bool OpToyType_Parse(
    const ::std::string& name, OpToyType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<OpToyType>(
    OpToyType_descriptor(), name, value);
}
// ===================================================================

class ReqOpToy : public ::google::protobuf::Message {
 public:
  ReqOpToy();
  virtual ~ReqOpToy();

  ReqOpToy(const ReqOpToy& from);

  inline ReqOpToy& operator=(const ReqOpToy& from) {
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
  static const ReqOpToy& default_instance();

  void Swap(ReqOpToy* other);

  // implements Message ----------------------------------------------

  ReqOpToy* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ReqOpToy& from);
  void MergeFrom(const ReqOpToy& from);
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

  // required .HelloKittyMsgData.OpToyType optype = 1;
  inline bool has_optype() const;
  inline void clear_optype();
  static const int kOptypeFieldNumber = 1;
  inline ::HelloKittyMsgData::OpToyType optype() const;
  inline void set_optype(::HelloKittyMsgData::OpToyType value);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.ReqOpToy)
 private:
  inline void set_has_optype();
  inline void clear_has_optype();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  int optype_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_toy_2eproto();
  friend void protobuf_AssignDesc_toy_2eproto();
  friend void protobuf_ShutdownFile_toy_2eproto();

  void InitAsDefaultInstance();
  static ReqOpToy* default_instance_;
};
// -------------------------------------------------------------------

class AckToy : public ::google::protobuf::Message {
 public:
  AckToy();
  virtual ~AckToy();

  AckToy(const AckToy& from);

  inline AckToy& operator=(const AckToy& from) {
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
  static const AckToy& default_instance();

  void Swap(AckToy* other);

  // implements Message ----------------------------------------------

  AckToy* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AckToy& from);
  void MergeFrom(const AckToy& from);
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

  // repeated uint32 toyid = 1;
  inline int toyid_size() const;
  inline void clear_toyid();
  static const int kToyidFieldNumber = 1;
  inline ::google::protobuf::uint32 toyid(int index) const;
  inline void set_toyid(int index, ::google::protobuf::uint32 value);
  inline void add_toyid(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      toyid() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_toyid();

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.AckToy)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > toyid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_toy_2eproto();
  friend void protobuf_AssignDesc_toy_2eproto();
  friend void protobuf_ShutdownFile_toy_2eproto();

  void InitAsDefaultInstance();
  static AckToy* default_instance_;
};
// -------------------------------------------------------------------

class AckRandToy : public ::google::protobuf::Message {
 public:
  AckRandToy();
  virtual ~AckRandToy();

  AckRandToy(const AckRandToy& from);

  inline AckRandToy& operator=(const AckRandToy& from) {
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
  static const AckRandToy& default_instance();

  void Swap(AckRandToy* other);

  // implements Message ----------------------------------------------

  AckRandToy* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AckRandToy& from);
  void MergeFrom(const AckRandToy& from);
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

  // required uint32 randtoyid = 1;
  inline bool has_randtoyid() const;
  inline void clear_randtoyid();
  static const int kRandtoyidFieldNumber = 1;
  inline ::google::protobuf::uint32 randtoyid() const;
  inline void set_randtoyid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.AckRandToy)
 private:
  inline void set_has_randtoyid();
  inline void clear_has_randtoyid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 randtoyid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_toy_2eproto();
  friend void protobuf_AssignDesc_toy_2eproto();
  friend void protobuf_ShutdownFile_toy_2eproto();

  void InitAsDefaultInstance();
  static AckRandToy* default_instance_;
};
// ===================================================================


// ===================================================================

// ReqOpToy

// required .HelloKittyMsgData.OpToyType optype = 1;
inline bool ReqOpToy::has_optype() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ReqOpToy::set_has_optype() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ReqOpToy::clear_has_optype() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ReqOpToy::clear_optype() {
  optype_ = 0;
  clear_has_optype();
}
inline ::HelloKittyMsgData::OpToyType ReqOpToy::optype() const {
  return static_cast< ::HelloKittyMsgData::OpToyType >(optype_);
}
inline void ReqOpToy::set_optype(::HelloKittyMsgData::OpToyType value) {
  assert(::HelloKittyMsgData::OpToyType_IsValid(value));
  set_has_optype();
  optype_ = value;
}

// -------------------------------------------------------------------

// AckToy

// repeated uint32 toyid = 1;
inline int AckToy::toyid_size() const {
  return toyid_.size();
}
inline void AckToy::clear_toyid() {
  toyid_.Clear();
}
inline ::google::protobuf::uint32 AckToy::toyid(int index) const {
  return toyid_.Get(index);
}
inline void AckToy::set_toyid(int index, ::google::protobuf::uint32 value) {
  toyid_.Set(index, value);
}
inline void AckToy::add_toyid(::google::protobuf::uint32 value) {
  toyid_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
AckToy::toyid() const {
  return toyid_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
AckToy::mutable_toyid() {
  return &toyid_;
}

// -------------------------------------------------------------------

// AckRandToy

// required uint32 randtoyid = 1;
inline bool AckRandToy::has_randtoyid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AckRandToy::set_has_randtoyid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AckRandToy::clear_has_randtoyid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AckRandToy::clear_randtoyid() {
  randtoyid_ = 0u;
  clear_has_randtoyid();
}
inline ::google::protobuf::uint32 AckRandToy::randtoyid() const {
  return randtoyid_;
}
inline void AckRandToy::set_randtoyid(::google::protobuf::uint32 value) {
  set_has_randtoyid();
  randtoyid_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace HelloKittyMsgData

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::HelloKittyMsgData::OpToyType>() {
  return ::HelloKittyMsgData::OpToyType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_toy_2eproto__INCLUDED