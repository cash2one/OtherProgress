// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GardenActivetyItem.proto

#ifndef PROTOBUF_GardenActivetyItem_2eproto__INCLUDED
#define PROTOBUF_GardenActivetyItem_2eproto__INCLUDED

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
void  protobuf_AddDesc_GardenActivetyItem_2eproto();
void protobuf_AssignDesc_GardenActivetyItem_2eproto();
void protobuf_ShutdownFile_GardenActivetyItem_2eproto();

class rubbish;
class rubbish_t_rubbish;

// ===================================================================

class rubbish_t_rubbish : public ::google::protobuf::Message {
 public:
  rubbish_t_rubbish();
  virtual ~rubbish_t_rubbish();

  rubbish_t_rubbish(const rubbish_t_rubbish& from);

  inline rubbish_t_rubbish& operator=(const rubbish_t_rubbish& from) {
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
  static const rubbish_t_rubbish& default_instance();

  void Swap(rubbish_t_rubbish* other);

  // implements Message ----------------------------------------------

  rubbish_t_rubbish* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const rubbish_t_rubbish& from);
  void MergeFrom(const rubbish_t_rubbish& from);
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

  // required uint32 type = 3;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 3;
  inline ::google::protobuf::uint32 type() const;
  inline void set_type(::google::protobuf::uint32 value);

  // required uint32 time = 4;
  inline bool has_time() const;
  inline void clear_time();
  static const int kTimeFieldNumber = 4;
  inline ::google::protobuf::uint32 time() const;
  inline void set_time(::google::protobuf::uint32 value);

  // required uint32 rate = 5;
  inline bool has_rate() const;
  inline void clear_rate();
  static const int kRateFieldNumber = 5;
  inline ::google::protobuf::uint32 rate() const;
  inline void set_rate(::google::protobuf::uint32 value);

  // required string reward = 6;
  inline bool has_reward() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 6;
  inline const ::std::string& reward() const;
  inline void set_reward(const ::std::string& value);
  inline void set_reward(const char* value);
  inline void set_reward(const char* value, size_t size);
  inline ::std::string* mutable_reward();
  inline ::std::string* release_reward();
  inline void set_allocated_reward(::std::string* reward);

  // @@protoc_insertion_point(class_scope:pb.rubbish.t_rubbish)
 private:
  inline void set_has_tbxid();
  inline void clear_has_tbxid();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_time();
  inline void clear_has_time();
  inline void set_has_rate();
  inline void clear_has_rate();
  inline void set_has_reward();
  inline void clear_has_reward();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 tbxid_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 type_;
  ::google::protobuf::uint32 time_;
  ::std::string* reward_;
  ::google::protobuf::uint32 rate_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(6 + 31) / 32];

  friend void  protobuf_AddDesc_GardenActivetyItem_2eproto();
  friend void protobuf_AssignDesc_GardenActivetyItem_2eproto();
  friend void protobuf_ShutdownFile_GardenActivetyItem_2eproto();

  void InitAsDefaultInstance();
  static rubbish_t_rubbish* default_instance_;
};
// -------------------------------------------------------------------

class rubbish : public ::google::protobuf::Message {
 public:
  rubbish();
  virtual ~rubbish();

  rubbish(const rubbish& from);

  inline rubbish& operator=(const rubbish& from) {
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
  static const rubbish& default_instance();

  void Swap(rubbish* other);

  // implements Message ----------------------------------------------

  rubbish* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const rubbish& from);
  void MergeFrom(const rubbish& from);
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

  typedef rubbish_t_rubbish t_rubbish;

  // accessors -------------------------------------------------------

  // repeated .pb.rubbish.t_rubbish datas = 1;
  inline int datas_size() const;
  inline void clear_datas();
  static const int kDatasFieldNumber = 1;
  inline const ::pb::rubbish_t_rubbish& datas(int index) const;
  inline ::pb::rubbish_t_rubbish* mutable_datas(int index);
  inline ::pb::rubbish_t_rubbish* add_datas();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::rubbish_t_rubbish >&
      datas() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::rubbish_t_rubbish >*
      mutable_datas();

  // @@protoc_insertion_point(class_scope:pb.rubbish)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::pb::rubbish_t_rubbish > datas_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_GardenActivetyItem_2eproto();
  friend void protobuf_AssignDesc_GardenActivetyItem_2eproto();
  friend void protobuf_ShutdownFile_GardenActivetyItem_2eproto();

  void InitAsDefaultInstance();
  static rubbish* default_instance_;
};
// ===================================================================


// ===================================================================

// rubbish_t_rubbish

// required uint32 tbxid = 1;
inline bool rubbish_t_rubbish::has_tbxid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void rubbish_t_rubbish::set_has_tbxid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void rubbish_t_rubbish::clear_has_tbxid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void rubbish_t_rubbish::clear_tbxid() {
  tbxid_ = 0u;
  clear_has_tbxid();
}
inline ::google::protobuf::uint32 rubbish_t_rubbish::tbxid() const {
  return tbxid_;
}
inline void rubbish_t_rubbish::set_tbxid(::google::protobuf::uint32 value) {
  set_has_tbxid();
  tbxid_ = value;
}

// required uint32 id = 2;
inline bool rubbish_t_rubbish::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void rubbish_t_rubbish::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void rubbish_t_rubbish::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void rubbish_t_rubbish::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 rubbish_t_rubbish::id() const {
  return id_;
}
inline void rubbish_t_rubbish::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required uint32 type = 3;
inline bool rubbish_t_rubbish::has_type() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void rubbish_t_rubbish::set_has_type() {
  _has_bits_[0] |= 0x00000004u;
}
inline void rubbish_t_rubbish::clear_has_type() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void rubbish_t_rubbish::clear_type() {
  type_ = 0u;
  clear_has_type();
}
inline ::google::protobuf::uint32 rubbish_t_rubbish::type() const {
  return type_;
}
inline void rubbish_t_rubbish::set_type(::google::protobuf::uint32 value) {
  set_has_type();
  type_ = value;
}

// required uint32 time = 4;
inline bool rubbish_t_rubbish::has_time() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void rubbish_t_rubbish::set_has_time() {
  _has_bits_[0] |= 0x00000008u;
}
inline void rubbish_t_rubbish::clear_has_time() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void rubbish_t_rubbish::clear_time() {
  time_ = 0u;
  clear_has_time();
}
inline ::google::protobuf::uint32 rubbish_t_rubbish::time() const {
  return time_;
}
inline void rubbish_t_rubbish::set_time(::google::protobuf::uint32 value) {
  set_has_time();
  time_ = value;
}

// required uint32 rate = 5;
inline bool rubbish_t_rubbish::has_rate() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void rubbish_t_rubbish::set_has_rate() {
  _has_bits_[0] |= 0x00000010u;
}
inline void rubbish_t_rubbish::clear_has_rate() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void rubbish_t_rubbish::clear_rate() {
  rate_ = 0u;
  clear_has_rate();
}
inline ::google::protobuf::uint32 rubbish_t_rubbish::rate() const {
  return rate_;
}
inline void rubbish_t_rubbish::set_rate(::google::protobuf::uint32 value) {
  set_has_rate();
  rate_ = value;
}

// required string reward = 6;
inline bool rubbish_t_rubbish::has_reward() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void rubbish_t_rubbish::set_has_reward() {
  _has_bits_[0] |= 0x00000020u;
}
inline void rubbish_t_rubbish::clear_has_reward() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void rubbish_t_rubbish::clear_reward() {
  if (reward_ != &::google::protobuf::internal::kEmptyString) {
    reward_->clear();
  }
  clear_has_reward();
}
inline const ::std::string& rubbish_t_rubbish::reward() const {
  return *reward_;
}
inline void rubbish_t_rubbish::set_reward(const ::std::string& value) {
  set_has_reward();
  if (reward_ == &::google::protobuf::internal::kEmptyString) {
    reward_ = new ::std::string;
  }
  reward_->assign(value);
}
inline void rubbish_t_rubbish::set_reward(const char* value) {
  set_has_reward();
  if (reward_ == &::google::protobuf::internal::kEmptyString) {
    reward_ = new ::std::string;
  }
  reward_->assign(value);
}
inline void rubbish_t_rubbish::set_reward(const char* value, size_t size) {
  set_has_reward();
  if (reward_ == &::google::protobuf::internal::kEmptyString) {
    reward_ = new ::std::string;
  }
  reward_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* rubbish_t_rubbish::mutable_reward() {
  set_has_reward();
  if (reward_ == &::google::protobuf::internal::kEmptyString) {
    reward_ = new ::std::string;
  }
  return reward_;
}
inline ::std::string* rubbish_t_rubbish::release_reward() {
  clear_has_reward();
  if (reward_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = reward_;
    reward_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void rubbish_t_rubbish::set_allocated_reward(::std::string* reward) {
  if (reward_ != &::google::protobuf::internal::kEmptyString) {
    delete reward_;
  }
  if (reward) {
    set_has_reward();
    reward_ = reward;
  } else {
    clear_has_reward();
    reward_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// rubbish

// repeated .pb.rubbish.t_rubbish datas = 1;
inline int rubbish::datas_size() const {
  return datas_.size();
}
inline void rubbish::clear_datas() {
  datas_.Clear();
}
inline const ::pb::rubbish_t_rubbish& rubbish::datas(int index) const {
  return datas_.Get(index);
}
inline ::pb::rubbish_t_rubbish* rubbish::mutable_datas(int index) {
  return datas_.Mutable(index);
}
inline ::pb::rubbish_t_rubbish* rubbish::add_datas() {
  return datas_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::rubbish_t_rubbish >&
rubbish::datas() const {
  return datas_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::rubbish_t_rubbish >*
rubbish::mutable_datas() {
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

#endif  // PROTOBUF_GardenActivetyItem_2eproto__INCLUDED
