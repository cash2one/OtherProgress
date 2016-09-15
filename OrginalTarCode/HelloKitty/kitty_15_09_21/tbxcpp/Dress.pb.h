// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Dress.proto

#ifndef PROTOBUF_Dress_2eproto__INCLUDED
#define PROTOBUF_Dress_2eproto__INCLUDED

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
void  protobuf_AddDesc_Dress_2eproto();
void protobuf_AssignDesc_Dress_2eproto();
void protobuf_ShutdownFile_Dress_2eproto();

class Dress;
class Dress_t_Dress;

// ===================================================================

class Dress_t_Dress : public ::google::protobuf::Message {
 public:
  Dress_t_Dress();
  virtual ~Dress_t_Dress();

  Dress_t_Dress(const Dress_t_Dress& from);

  inline Dress_t_Dress& operator=(const Dress_t_Dress& from) {
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
  static const Dress_t_Dress& default_instance();

  void Swap(Dress_t_Dress* other);

  // implements Message ----------------------------------------------

  Dress_t_Dress* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Dress_t_Dress& from);
  void MergeFrom(const Dress_t_Dress& from);
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

  // required string material = 4;
  inline bool has_material() const;
  inline void clear_material();
  static const int kMaterialFieldNumber = 4;
  inline const ::std::string& material() const;
  inline void set_material(const ::std::string& value);
  inline void set_material(const char* value);
  inline void set_material(const char* value, size_t size);
  inline ::std::string* mutable_material();
  inline ::std::string* release_material();
  inline void set_allocated_material(::std::string* material);

  // required string buffer = 5;
  inline bool has_buffer() const;
  inline void clear_buffer();
  static const int kBufferFieldNumber = 5;
  inline const ::std::string& buffer() const;
  inline void set_buffer(const ::std::string& value);
  inline void set_buffer(const char* value);
  inline void set_buffer(const char* value, size_t size);
  inline ::std::string* mutable_buffer();
  inline ::std::string* release_buffer();
  inline void set_allocated_buffer(::std::string* buffer);

  // required uint32 price = 6;
  inline bool has_price() const;
  inline void clear_price();
  static const int kPriceFieldNumber = 6;
  inline ::google::protobuf::uint32 price() const;
  inline void set_price(::google::protobuf::uint32 value);

  // required string atlas = 7;
  inline bool has_atlas() const;
  inline void clear_atlas();
  static const int kAtlasFieldNumber = 7;
  inline const ::std::string& atlas() const;
  inline void set_atlas(const ::std::string& value);
  inline void set_atlas(const char* value);
  inline void set_atlas(const char* value, size_t size);
  inline ::std::string* mutable_atlas();
  inline ::std::string* release_atlas();
  inline void set_allocated_atlas(::std::string* atlas);

  // @@protoc_insertion_point(class_scope:pb.Dress.t_Dress)
 private:
  inline void set_has_tbxid();
  inline void clear_has_tbxid();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_level();
  inline void clear_has_level();
  inline void set_has_material();
  inline void clear_has_material();
  inline void set_has_buffer();
  inline void clear_has_buffer();
  inline void set_has_price();
  inline void clear_has_price();
  inline void set_has_atlas();
  inline void clear_has_atlas();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 tbxid_;
  ::google::protobuf::uint32 id_;
  ::std::string* material_;
  ::google::protobuf::uint32 level_;
  ::google::protobuf::uint32 price_;
  ::std::string* buffer_;
  ::std::string* atlas_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];

  friend void  protobuf_AddDesc_Dress_2eproto();
  friend void protobuf_AssignDesc_Dress_2eproto();
  friend void protobuf_ShutdownFile_Dress_2eproto();

  void InitAsDefaultInstance();
  static Dress_t_Dress* default_instance_;
};
// -------------------------------------------------------------------

class Dress : public ::google::protobuf::Message {
 public:
  Dress();
  virtual ~Dress();

  Dress(const Dress& from);

  inline Dress& operator=(const Dress& from) {
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
  static const Dress& default_instance();

  void Swap(Dress* other);

  // implements Message ----------------------------------------------

  Dress* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Dress& from);
  void MergeFrom(const Dress& from);
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

  typedef Dress_t_Dress t_Dress;

  // accessors -------------------------------------------------------

  // repeated .pb.Dress.t_Dress datas = 1;
  inline int datas_size() const;
  inline void clear_datas();
  static const int kDatasFieldNumber = 1;
  inline const ::pb::Dress_t_Dress& datas(int index) const;
  inline ::pb::Dress_t_Dress* mutable_datas(int index);
  inline ::pb::Dress_t_Dress* add_datas();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::Dress_t_Dress >&
      datas() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::Dress_t_Dress >*
      mutable_datas();

  // @@protoc_insertion_point(class_scope:pb.Dress)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::pb::Dress_t_Dress > datas_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_Dress_2eproto();
  friend void protobuf_AssignDesc_Dress_2eproto();
  friend void protobuf_ShutdownFile_Dress_2eproto();

  void InitAsDefaultInstance();
  static Dress* default_instance_;
};
// ===================================================================


// ===================================================================

// Dress_t_Dress

// required uint32 tbxid = 1;
inline bool Dress_t_Dress::has_tbxid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Dress_t_Dress::set_has_tbxid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Dress_t_Dress::clear_has_tbxid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Dress_t_Dress::clear_tbxid() {
  tbxid_ = 0u;
  clear_has_tbxid();
}
inline ::google::protobuf::uint32 Dress_t_Dress::tbxid() const {
  return tbxid_;
}
inline void Dress_t_Dress::set_tbxid(::google::protobuf::uint32 value) {
  set_has_tbxid();
  tbxid_ = value;
}

// required uint32 id = 2;
inline bool Dress_t_Dress::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Dress_t_Dress::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Dress_t_Dress::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Dress_t_Dress::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 Dress_t_Dress::id() const {
  return id_;
}
inline void Dress_t_Dress::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required uint32 level = 3;
inline bool Dress_t_Dress::has_level() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Dress_t_Dress::set_has_level() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Dress_t_Dress::clear_has_level() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Dress_t_Dress::clear_level() {
  level_ = 0u;
  clear_has_level();
}
inline ::google::protobuf::uint32 Dress_t_Dress::level() const {
  return level_;
}
inline void Dress_t_Dress::set_level(::google::protobuf::uint32 value) {
  set_has_level();
  level_ = value;
}

// required string material = 4;
inline bool Dress_t_Dress::has_material() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Dress_t_Dress::set_has_material() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Dress_t_Dress::clear_has_material() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Dress_t_Dress::clear_material() {
  if (material_ != &::google::protobuf::internal::kEmptyString) {
    material_->clear();
  }
  clear_has_material();
}
inline const ::std::string& Dress_t_Dress::material() const {
  return *material_;
}
inline void Dress_t_Dress::set_material(const ::std::string& value) {
  set_has_material();
  if (material_ == &::google::protobuf::internal::kEmptyString) {
    material_ = new ::std::string;
  }
  material_->assign(value);
}
inline void Dress_t_Dress::set_material(const char* value) {
  set_has_material();
  if (material_ == &::google::protobuf::internal::kEmptyString) {
    material_ = new ::std::string;
  }
  material_->assign(value);
}
inline void Dress_t_Dress::set_material(const char* value, size_t size) {
  set_has_material();
  if (material_ == &::google::protobuf::internal::kEmptyString) {
    material_ = new ::std::string;
  }
  material_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Dress_t_Dress::mutable_material() {
  set_has_material();
  if (material_ == &::google::protobuf::internal::kEmptyString) {
    material_ = new ::std::string;
  }
  return material_;
}
inline ::std::string* Dress_t_Dress::release_material() {
  clear_has_material();
  if (material_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = material_;
    material_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Dress_t_Dress::set_allocated_material(::std::string* material) {
  if (material_ != &::google::protobuf::internal::kEmptyString) {
    delete material_;
  }
  if (material) {
    set_has_material();
    material_ = material;
  } else {
    clear_has_material();
    material_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string buffer = 5;
inline bool Dress_t_Dress::has_buffer() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Dress_t_Dress::set_has_buffer() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Dress_t_Dress::clear_has_buffer() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Dress_t_Dress::clear_buffer() {
  if (buffer_ != &::google::protobuf::internal::kEmptyString) {
    buffer_->clear();
  }
  clear_has_buffer();
}
inline const ::std::string& Dress_t_Dress::buffer() const {
  return *buffer_;
}
inline void Dress_t_Dress::set_buffer(const ::std::string& value) {
  set_has_buffer();
  if (buffer_ == &::google::protobuf::internal::kEmptyString) {
    buffer_ = new ::std::string;
  }
  buffer_->assign(value);
}
inline void Dress_t_Dress::set_buffer(const char* value) {
  set_has_buffer();
  if (buffer_ == &::google::protobuf::internal::kEmptyString) {
    buffer_ = new ::std::string;
  }
  buffer_->assign(value);
}
inline void Dress_t_Dress::set_buffer(const char* value, size_t size) {
  set_has_buffer();
  if (buffer_ == &::google::protobuf::internal::kEmptyString) {
    buffer_ = new ::std::string;
  }
  buffer_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Dress_t_Dress::mutable_buffer() {
  set_has_buffer();
  if (buffer_ == &::google::protobuf::internal::kEmptyString) {
    buffer_ = new ::std::string;
  }
  return buffer_;
}
inline ::std::string* Dress_t_Dress::release_buffer() {
  clear_has_buffer();
  if (buffer_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = buffer_;
    buffer_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Dress_t_Dress::set_allocated_buffer(::std::string* buffer) {
  if (buffer_ != &::google::protobuf::internal::kEmptyString) {
    delete buffer_;
  }
  if (buffer) {
    set_has_buffer();
    buffer_ = buffer;
  } else {
    clear_has_buffer();
    buffer_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required uint32 price = 6;
inline bool Dress_t_Dress::has_price() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Dress_t_Dress::set_has_price() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Dress_t_Dress::clear_has_price() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Dress_t_Dress::clear_price() {
  price_ = 0u;
  clear_has_price();
}
inline ::google::protobuf::uint32 Dress_t_Dress::price() const {
  return price_;
}
inline void Dress_t_Dress::set_price(::google::protobuf::uint32 value) {
  set_has_price();
  price_ = value;
}

// required string atlas = 7;
inline bool Dress_t_Dress::has_atlas() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void Dress_t_Dress::set_has_atlas() {
  _has_bits_[0] |= 0x00000040u;
}
inline void Dress_t_Dress::clear_has_atlas() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void Dress_t_Dress::clear_atlas() {
  if (atlas_ != &::google::protobuf::internal::kEmptyString) {
    atlas_->clear();
  }
  clear_has_atlas();
}
inline const ::std::string& Dress_t_Dress::atlas() const {
  return *atlas_;
}
inline void Dress_t_Dress::set_atlas(const ::std::string& value) {
  set_has_atlas();
  if (atlas_ == &::google::protobuf::internal::kEmptyString) {
    atlas_ = new ::std::string;
  }
  atlas_->assign(value);
}
inline void Dress_t_Dress::set_atlas(const char* value) {
  set_has_atlas();
  if (atlas_ == &::google::protobuf::internal::kEmptyString) {
    atlas_ = new ::std::string;
  }
  atlas_->assign(value);
}
inline void Dress_t_Dress::set_atlas(const char* value, size_t size) {
  set_has_atlas();
  if (atlas_ == &::google::protobuf::internal::kEmptyString) {
    atlas_ = new ::std::string;
  }
  atlas_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Dress_t_Dress::mutable_atlas() {
  set_has_atlas();
  if (atlas_ == &::google::protobuf::internal::kEmptyString) {
    atlas_ = new ::std::string;
  }
  return atlas_;
}
inline ::std::string* Dress_t_Dress::release_atlas() {
  clear_has_atlas();
  if (atlas_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = atlas_;
    atlas_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Dress_t_Dress::set_allocated_atlas(::std::string* atlas) {
  if (atlas_ != &::google::protobuf::internal::kEmptyString) {
    delete atlas_;
  }
  if (atlas) {
    set_has_atlas();
    atlas_ = atlas;
  } else {
    clear_has_atlas();
    atlas_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// Dress

// repeated .pb.Dress.t_Dress datas = 1;
inline int Dress::datas_size() const {
  return datas_.size();
}
inline void Dress::clear_datas() {
  datas_.Clear();
}
inline const ::pb::Dress_t_Dress& Dress::datas(int index) const {
  return datas_.Get(index);
}
inline ::pb::Dress_t_Dress* Dress::mutable_datas(int index) {
  return datas_.Mutable(index);
}
inline ::pb::Dress_t_Dress* Dress::add_datas() {
  return datas_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::Dress_t_Dress >&
Dress::datas() const {
  return datas_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::Dress_t_Dress >*
Dress::mutable_datas() {
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

#endif  // PROTOBUF_Dress_2eproto__INCLUDED