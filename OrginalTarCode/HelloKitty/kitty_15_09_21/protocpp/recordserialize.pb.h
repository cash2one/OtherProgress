// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: recordserialize.proto

#ifndef PROTOBUF_recordserialize_2eproto__INCLUDED
#define PROTOBUF_recordserialize_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace HelloKittyMsgData {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_recordserialize_2eproto();
void protobuf_AssignDesc_recordserialize_2eproto();
void protobuf_ShutdownFile_recordserialize_2eproto();

class RecordSerialize;

// ===================================================================

class RecordSerialize : public ::google::protobuf::Message {
 public:
  RecordSerialize();
  virtual ~RecordSerialize();

  RecordSerialize(const RecordSerialize& from);

  inline RecordSerialize& operator=(const RecordSerialize& from) {
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
  static const RecordSerialize& default_instance();

  void Swap(RecordSerialize* other);

  // implements Message ----------------------------------------------

  RecordSerialize* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RecordSerialize& from);
  void MergeFrom(const RecordSerialize& from);
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

  // repeated .HelloKittyMsgData.SellPaperCell advertise = 1;
  inline int advertise_size() const;
  inline void clear_advertise();
  static const int kAdvertiseFieldNumber = 1;
  inline const ::HelloKittyMsgData::SellPaperCell& advertise(int index) const;
  inline ::HelloKittyMsgData::SellPaperCell* mutable_advertise(int index);
  inline ::HelloKittyMsgData::SellPaperCell* add_advertise();
  inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::SellPaperCell >&
      advertise() const;
  inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::SellPaperCell >*
      mutable_advertise();

  // @@protoc_insertion_point(class_scope:HelloKittyMsgData.RecordSerialize)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::SellPaperCell > advertise_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_recordserialize_2eproto();
  friend void protobuf_AssignDesc_recordserialize_2eproto();
  friend void protobuf_ShutdownFile_recordserialize_2eproto();

  void InitAsDefaultInstance();
  static RecordSerialize* default_instance_;
};
// ===================================================================


// ===================================================================

// RecordSerialize

// repeated .HelloKittyMsgData.SellPaperCell advertise = 1;
inline int RecordSerialize::advertise_size() const {
  return advertise_.size();
}
inline void RecordSerialize::clear_advertise() {
  advertise_.Clear();
}
inline const ::HelloKittyMsgData::SellPaperCell& RecordSerialize::advertise(int index) const {
  return advertise_.Get(index);
}
inline ::HelloKittyMsgData::SellPaperCell* RecordSerialize::mutable_advertise(int index) {
  return advertise_.Mutable(index);
}
inline ::HelloKittyMsgData::SellPaperCell* RecordSerialize::add_advertise() {
  return advertise_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::SellPaperCell >&
RecordSerialize::advertise() const {
  return advertise_;
}
inline ::google::protobuf::RepeatedPtrField< ::HelloKittyMsgData::SellPaperCell >*
RecordSerialize::mutable_advertise() {
  return &advertise_;
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

#endif  // PROTOBUF_recordserialize_2eproto__INCLUDED
