// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Localization.proto

#ifndef PROTOBUF_Localization_2eproto__INCLUDED
#define PROTOBUF_Localization_2eproto__INCLUDED

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
void  protobuf_AddDesc_Localization_2eproto();
void protobuf_AssignDesc_Localization_2eproto();
void protobuf_ShutdownFile_Localization_2eproto();

class Localization;
class Localization_t_Localization;

// ===================================================================

class Localization_t_Localization : public ::google::protobuf::Message {
 public:
  Localization_t_Localization();
  virtual ~Localization_t_Localization();

  Localization_t_Localization(const Localization_t_Localization& from);

  inline Localization_t_Localization& operator=(const Localization_t_Localization& from) {
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
  static const Localization_t_Localization& default_instance();

  void Swap(Localization_t_Localization* other);

  // implements Message ----------------------------------------------

  Localization_t_Localization* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Localization_t_Localization& from);
  void MergeFrom(const Localization_t_Localization& from);
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

  // required string id = 2;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 2;
  inline const ::std::string& id() const;
  inline void set_id(const ::std::string& value);
  inline void set_id(const char* value);
  inline void set_id(const char* value, size_t size);
  inline ::std::string* mutable_id();
  inline ::std::string* release_id();
  inline void set_allocated_id(::std::string* id);

  // required string English = 3;
  inline bool has_english() const;
  inline void clear_english();
  static const int kEnglishFieldNumber = 3;
  inline const ::std::string& english() const;
  inline void set_english(const ::std::string& value);
  inline void set_english(const char* value);
  inline void set_english(const char* value, size_t size);
  inline ::std::string* mutable_english();
  inline ::std::string* release_english();
  inline void set_allocated_english(::std::string* english);

  // required string Chinese = 4;
  inline bool has_chinese() const;
  inline void clear_chinese();
  static const int kChineseFieldNumber = 4;
  inline const ::std::string& chinese() const;
  inline void set_chinese(const ::std::string& value);
  inline void set_chinese(const char* value);
  inline void set_chinese(const char* value, size_t size);
  inline ::std::string* mutable_chinese();
  inline ::std::string* release_chinese();
  inline void set_allocated_chinese(::std::string* chinese);

  // required string Japanese = 5;
  inline bool has_japanese() const;
  inline void clear_japanese();
  static const int kJapaneseFieldNumber = 5;
  inline const ::std::string& japanese() const;
  inline void set_japanese(const ::std::string& value);
  inline void set_japanese(const char* value);
  inline void set_japanese(const char* value, size_t size);
  inline ::std::string* mutable_japanese();
  inline ::std::string* release_japanese();
  inline void set_allocated_japanese(::std::string* japanese);

  // @@protoc_insertion_point(class_scope:pb.Localization.t_Localization)
 private:
  inline void set_has_tbxid();
  inline void clear_has_tbxid();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_english();
  inline void clear_has_english();
  inline void set_has_chinese();
  inline void clear_has_chinese();
  inline void set_has_japanese();
  inline void clear_has_japanese();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* id_;
  ::std::string* english_;
  ::std::string* chinese_;
  ::std::string* japanese_;
  ::google::protobuf::uint32 tbxid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];

  friend void  protobuf_AddDesc_Localization_2eproto();
  friend void protobuf_AssignDesc_Localization_2eproto();
  friend void protobuf_ShutdownFile_Localization_2eproto();

  void InitAsDefaultInstance();
  static Localization_t_Localization* default_instance_;
};
// -------------------------------------------------------------------

class Localization : public ::google::protobuf::Message {
 public:
  Localization();
  virtual ~Localization();

  Localization(const Localization& from);

  inline Localization& operator=(const Localization& from) {
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
  static const Localization& default_instance();

  void Swap(Localization* other);

  // implements Message ----------------------------------------------

  Localization* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Localization& from);
  void MergeFrom(const Localization& from);
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

  typedef Localization_t_Localization t_Localization;

  // accessors -------------------------------------------------------

  // repeated .pb.Localization.t_Localization datas = 1;
  inline int datas_size() const;
  inline void clear_datas();
  static const int kDatasFieldNumber = 1;
  inline const ::pb::Localization_t_Localization& datas(int index) const;
  inline ::pb::Localization_t_Localization* mutable_datas(int index);
  inline ::pb::Localization_t_Localization* add_datas();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::Localization_t_Localization >&
      datas() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::Localization_t_Localization >*
      mutable_datas();

  // @@protoc_insertion_point(class_scope:pb.Localization)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::pb::Localization_t_Localization > datas_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_Localization_2eproto();
  friend void protobuf_AssignDesc_Localization_2eproto();
  friend void protobuf_ShutdownFile_Localization_2eproto();

  void InitAsDefaultInstance();
  static Localization* default_instance_;
};
// ===================================================================


// ===================================================================

// Localization_t_Localization

// required uint32 tbxid = 1;
inline bool Localization_t_Localization::has_tbxid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Localization_t_Localization::set_has_tbxid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Localization_t_Localization::clear_has_tbxid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Localization_t_Localization::clear_tbxid() {
  tbxid_ = 0u;
  clear_has_tbxid();
}
inline ::google::protobuf::uint32 Localization_t_Localization::tbxid() const {
  return tbxid_;
}
inline void Localization_t_Localization::set_tbxid(::google::protobuf::uint32 value) {
  set_has_tbxid();
  tbxid_ = value;
}

// required string id = 2;
inline bool Localization_t_Localization::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Localization_t_Localization::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Localization_t_Localization::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Localization_t_Localization::clear_id() {
  if (id_ != &::google::protobuf::internal::kEmptyString) {
    id_->clear();
  }
  clear_has_id();
}
inline const ::std::string& Localization_t_Localization::id() const {
  return *id_;
}
inline void Localization_t_Localization::set_id(const ::std::string& value) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::kEmptyString) {
    id_ = new ::std::string;
  }
  id_->assign(value);
}
inline void Localization_t_Localization::set_id(const char* value) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::kEmptyString) {
    id_ = new ::std::string;
  }
  id_->assign(value);
}
inline void Localization_t_Localization::set_id(const char* value, size_t size) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::kEmptyString) {
    id_ = new ::std::string;
  }
  id_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Localization_t_Localization::mutable_id() {
  set_has_id();
  if (id_ == &::google::protobuf::internal::kEmptyString) {
    id_ = new ::std::string;
  }
  return id_;
}
inline ::std::string* Localization_t_Localization::release_id() {
  clear_has_id();
  if (id_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = id_;
    id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Localization_t_Localization::set_allocated_id(::std::string* id) {
  if (id_ != &::google::protobuf::internal::kEmptyString) {
    delete id_;
  }
  if (id) {
    set_has_id();
    id_ = id;
  } else {
    clear_has_id();
    id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string English = 3;
inline bool Localization_t_Localization::has_english() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Localization_t_Localization::set_has_english() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Localization_t_Localization::clear_has_english() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Localization_t_Localization::clear_english() {
  if (english_ != &::google::protobuf::internal::kEmptyString) {
    english_->clear();
  }
  clear_has_english();
}
inline const ::std::string& Localization_t_Localization::english() const {
  return *english_;
}
inline void Localization_t_Localization::set_english(const ::std::string& value) {
  set_has_english();
  if (english_ == &::google::protobuf::internal::kEmptyString) {
    english_ = new ::std::string;
  }
  english_->assign(value);
}
inline void Localization_t_Localization::set_english(const char* value) {
  set_has_english();
  if (english_ == &::google::protobuf::internal::kEmptyString) {
    english_ = new ::std::string;
  }
  english_->assign(value);
}
inline void Localization_t_Localization::set_english(const char* value, size_t size) {
  set_has_english();
  if (english_ == &::google::protobuf::internal::kEmptyString) {
    english_ = new ::std::string;
  }
  english_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Localization_t_Localization::mutable_english() {
  set_has_english();
  if (english_ == &::google::protobuf::internal::kEmptyString) {
    english_ = new ::std::string;
  }
  return english_;
}
inline ::std::string* Localization_t_Localization::release_english() {
  clear_has_english();
  if (english_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = english_;
    english_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Localization_t_Localization::set_allocated_english(::std::string* english) {
  if (english_ != &::google::protobuf::internal::kEmptyString) {
    delete english_;
  }
  if (english) {
    set_has_english();
    english_ = english;
  } else {
    clear_has_english();
    english_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string Chinese = 4;
inline bool Localization_t_Localization::has_chinese() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Localization_t_Localization::set_has_chinese() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Localization_t_Localization::clear_has_chinese() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Localization_t_Localization::clear_chinese() {
  if (chinese_ != &::google::protobuf::internal::kEmptyString) {
    chinese_->clear();
  }
  clear_has_chinese();
}
inline const ::std::string& Localization_t_Localization::chinese() const {
  return *chinese_;
}
inline void Localization_t_Localization::set_chinese(const ::std::string& value) {
  set_has_chinese();
  if (chinese_ == &::google::protobuf::internal::kEmptyString) {
    chinese_ = new ::std::string;
  }
  chinese_->assign(value);
}
inline void Localization_t_Localization::set_chinese(const char* value) {
  set_has_chinese();
  if (chinese_ == &::google::protobuf::internal::kEmptyString) {
    chinese_ = new ::std::string;
  }
  chinese_->assign(value);
}
inline void Localization_t_Localization::set_chinese(const char* value, size_t size) {
  set_has_chinese();
  if (chinese_ == &::google::protobuf::internal::kEmptyString) {
    chinese_ = new ::std::string;
  }
  chinese_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Localization_t_Localization::mutable_chinese() {
  set_has_chinese();
  if (chinese_ == &::google::protobuf::internal::kEmptyString) {
    chinese_ = new ::std::string;
  }
  return chinese_;
}
inline ::std::string* Localization_t_Localization::release_chinese() {
  clear_has_chinese();
  if (chinese_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = chinese_;
    chinese_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Localization_t_Localization::set_allocated_chinese(::std::string* chinese) {
  if (chinese_ != &::google::protobuf::internal::kEmptyString) {
    delete chinese_;
  }
  if (chinese) {
    set_has_chinese();
    chinese_ = chinese;
  } else {
    clear_has_chinese();
    chinese_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string Japanese = 5;
inline bool Localization_t_Localization::has_japanese() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Localization_t_Localization::set_has_japanese() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Localization_t_Localization::clear_has_japanese() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Localization_t_Localization::clear_japanese() {
  if (japanese_ != &::google::protobuf::internal::kEmptyString) {
    japanese_->clear();
  }
  clear_has_japanese();
}
inline const ::std::string& Localization_t_Localization::japanese() const {
  return *japanese_;
}
inline void Localization_t_Localization::set_japanese(const ::std::string& value) {
  set_has_japanese();
  if (japanese_ == &::google::protobuf::internal::kEmptyString) {
    japanese_ = new ::std::string;
  }
  japanese_->assign(value);
}
inline void Localization_t_Localization::set_japanese(const char* value) {
  set_has_japanese();
  if (japanese_ == &::google::protobuf::internal::kEmptyString) {
    japanese_ = new ::std::string;
  }
  japanese_->assign(value);
}
inline void Localization_t_Localization::set_japanese(const char* value, size_t size) {
  set_has_japanese();
  if (japanese_ == &::google::protobuf::internal::kEmptyString) {
    japanese_ = new ::std::string;
  }
  japanese_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Localization_t_Localization::mutable_japanese() {
  set_has_japanese();
  if (japanese_ == &::google::protobuf::internal::kEmptyString) {
    japanese_ = new ::std::string;
  }
  return japanese_;
}
inline ::std::string* Localization_t_Localization::release_japanese() {
  clear_has_japanese();
  if (japanese_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = japanese_;
    japanese_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Localization_t_Localization::set_allocated_japanese(::std::string* japanese) {
  if (japanese_ != &::google::protobuf::internal::kEmptyString) {
    delete japanese_;
  }
  if (japanese) {
    set_has_japanese();
    japanese_ = japanese;
  } else {
    clear_has_japanese();
    japanese_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// Localization

// repeated .pb.Localization.t_Localization datas = 1;
inline int Localization::datas_size() const {
  return datas_.size();
}
inline void Localization::clear_datas() {
  datas_.Clear();
}
inline const ::pb::Localization_t_Localization& Localization::datas(int index) const {
  return datas_.Get(index);
}
inline ::pb::Localization_t_Localization* Localization::mutable_datas(int index) {
  return datas_.Mutable(index);
}
inline ::pb::Localization_t_Localization* Localization::add_datas() {
  return datas_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::Localization_t_Localization >&
Localization::datas() const {
  return datas_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::Localization_t_Localization >*
Localization::mutable_datas() {
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

#endif  // PROTOBUF_Localization_2eproto__INCLUDED
