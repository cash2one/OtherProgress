// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: TaskInfo.proto

#ifndef PROTOBUF_TaskInfo_2eproto__INCLUDED
#define PROTOBUF_TaskInfo_2eproto__INCLUDED

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
void  protobuf_AddDesc_TaskInfo_2eproto();
void protobuf_AssignDesc_TaskInfo_2eproto();
void protobuf_ShutdownFile_TaskInfo_2eproto();

class Task;
class Task_t_Task;

// ===================================================================

class Task_t_Task : public ::google::protobuf::Message {
 public:
  Task_t_Task();
  virtual ~Task_t_Task();

  Task_t_Task(const Task_t_Task& from);

  inline Task_t_Task& operator=(const Task_t_Task& from) {
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
  static const Task_t_Task& default_instance();

  void Swap(Task_t_Task* other);

  // implements Message ----------------------------------------------

  Task_t_Task* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Task_t_Task& from);
  void MergeFrom(const Task_t_Task& from);
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

  // required string title = 3;
  inline bool has_title() const;
  inline void clear_title();
  static const int kTitleFieldNumber = 3;
  inline const ::std::string& title() const;
  inline void set_title(const ::std::string& value);
  inline void set_title(const char* value);
  inline void set_title(const char* value, size_t size);
  inline ::std::string* mutable_title();
  inline ::std::string* release_title();
  inline void set_allocated_title(::std::string* title);

  // required string pre_id = 4;
  inline bool has_pre_id() const;
  inline void clear_pre_id();
  static const int kPreIdFieldNumber = 4;
  inline const ::std::string& pre_id() const;
  inline void set_pre_id(const ::std::string& value);
  inline void set_pre_id(const char* value);
  inline void set_pre_id(const char* value, size_t size);
  inline ::std::string* mutable_pre_id();
  inline ::std::string* release_pre_id();
  inline void set_allocated_pre_id(::std::string* pre_id);

  // required uint32 sub = 5;
  inline bool has_sub() const;
  inline void clear_sub();
  static const int kSubFieldNumber = 5;
  inline ::google::protobuf::uint32 sub() const;
  inline void set_sub(::google::protobuf::uint32 value);

  // required uint32 type = 6;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 6;
  inline ::google::protobuf::uint32 type() const;
  inline void set_type(::google::protobuf::uint32 value);

  // required uint32 pre_level = 7;
  inline bool has_pre_level() const;
  inline void clear_pre_level();
  static const int kPreLevelFieldNumber = 7;
  inline ::google::protobuf::uint32 pre_level() const;
  inline void set_pre_level(::google::protobuf::uint32 value);

  // required uint32 target_type = 8;
  inline bool has_target_type() const;
  inline void clear_target_type();
  static const int kTargetTypeFieldNumber = 8;
  inline ::google::protobuf::uint32 target_type() const;
  inline void set_target_type(::google::protobuf::uint32 value);

  // required string target = 9;
  inline bool has_target() const;
  inline void clear_target();
  static const int kTargetFieldNumber = 9;
  inline const ::std::string& target() const;
  inline void set_target(const ::std::string& value);
  inline void set_target(const char* value);
  inline void set_target(const char* value, size_t size);
  inline ::std::string* mutable_target();
  inline ::std::string* release_target();
  inline void set_allocated_target(::std::string* target);

  // required string target_content = 10;
  inline bool has_target_content() const;
  inline void clear_target_content();
  static const int kTargetContentFieldNumber = 10;
  inline const ::std::string& target_content() const;
  inline void set_target_content(const ::std::string& value);
  inline void set_target_content(const char* value);
  inline void set_target_content(const char* value, size_t size);
  inline ::std::string* mutable_target_content();
  inline ::std::string* release_target_content();
  inline void set_allocated_target_content(::std::string* target_content);

  // required string reward = 11;
  inline bool has_reward() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 11;
  inline const ::std::string& reward() const;
  inline void set_reward(const ::std::string& value);
  inline void set_reward(const char* value);
  inline void set_reward(const char* value, size_t size);
  inline ::std::string* mutable_reward();
  inline ::std::string* release_reward();
  inline void set_allocated_reward(::std::string* reward);

  // required string icon = 12;
  inline bool has_icon() const;
  inline void clear_icon();
  static const int kIconFieldNumber = 12;
  inline const ::std::string& icon() const;
  inline void set_icon(const ::std::string& value);
  inline void set_icon(const char* value);
  inline void set_icon(const char* value, size_t size);
  inline ::std::string* mutable_icon();
  inline ::std::string* release_icon();
  inline void set_allocated_icon(::std::string* icon);

  // required uint32 guideType = 13;
  inline bool has_guidetype() const;
  inline void clear_guidetype();
  static const int kGuideTypeFieldNumber = 13;
  inline ::google::protobuf::uint32 guidetype() const;
  inline void set_guidetype(::google::protobuf::uint32 value);

  // required string guideValue = 14;
  inline bool has_guidevalue() const;
  inline void clear_guidevalue();
  static const int kGuideValueFieldNumber = 14;
  inline const ::std::string& guidevalue() const;
  inline void set_guidevalue(const ::std::string& value);
  inline void set_guidevalue(const char* value);
  inline void set_guidevalue(const char* value, size_t size);
  inline ::std::string* mutable_guidevalue();
  inline ::std::string* release_guidevalue();
  inline void set_allocated_guidevalue(::std::string* guidevalue);

  // @@protoc_insertion_point(class_scope:pb.Task.t_Task)
 private:
  inline void set_has_tbxid();
  inline void clear_has_tbxid();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_title();
  inline void clear_has_title();
  inline void set_has_pre_id();
  inline void clear_has_pre_id();
  inline void set_has_sub();
  inline void clear_has_sub();
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_pre_level();
  inline void clear_has_pre_level();
  inline void set_has_target_type();
  inline void clear_has_target_type();
  inline void set_has_target();
  inline void clear_has_target();
  inline void set_has_target_content();
  inline void clear_has_target_content();
  inline void set_has_reward();
  inline void clear_has_reward();
  inline void set_has_icon();
  inline void clear_has_icon();
  inline void set_has_guidetype();
  inline void clear_has_guidetype();
  inline void set_has_guidevalue();
  inline void clear_has_guidevalue();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 tbxid_;
  ::google::protobuf::uint32 id_;
  ::std::string* title_;
  ::std::string* pre_id_;
  ::google::protobuf::uint32 sub_;
  ::google::protobuf::uint32 type_;
  ::google::protobuf::uint32 pre_level_;
  ::google::protobuf::uint32 target_type_;
  ::std::string* target_;
  ::std::string* target_content_;
  ::std::string* reward_;
  ::std::string* icon_;
  ::std::string* guidevalue_;
  ::google::protobuf::uint32 guidetype_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(14 + 31) / 32];

  friend void  protobuf_AddDesc_TaskInfo_2eproto();
  friend void protobuf_AssignDesc_TaskInfo_2eproto();
  friend void protobuf_ShutdownFile_TaskInfo_2eproto();

  void InitAsDefaultInstance();
  static Task_t_Task* default_instance_;
};
// -------------------------------------------------------------------

class Task : public ::google::protobuf::Message {
 public:
  Task();
  virtual ~Task();

  Task(const Task& from);

  inline Task& operator=(const Task& from) {
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
  static const Task& default_instance();

  void Swap(Task* other);

  // implements Message ----------------------------------------------

  Task* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Task& from);
  void MergeFrom(const Task& from);
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

  typedef Task_t_Task t_Task;

  // accessors -------------------------------------------------------

  // repeated .pb.Task.t_Task datas = 1;
  inline int datas_size() const;
  inline void clear_datas();
  static const int kDatasFieldNumber = 1;
  inline const ::pb::Task_t_Task& datas(int index) const;
  inline ::pb::Task_t_Task* mutable_datas(int index);
  inline ::pb::Task_t_Task* add_datas();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::Task_t_Task >&
      datas() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::Task_t_Task >*
      mutable_datas();

  // @@protoc_insertion_point(class_scope:pb.Task)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::pb::Task_t_Task > datas_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_TaskInfo_2eproto();
  friend void protobuf_AssignDesc_TaskInfo_2eproto();
  friend void protobuf_ShutdownFile_TaskInfo_2eproto();

  void InitAsDefaultInstance();
  static Task* default_instance_;
};
// ===================================================================


// ===================================================================

// Task_t_Task

// required uint32 tbxid = 1;
inline bool Task_t_Task::has_tbxid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Task_t_Task::set_has_tbxid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Task_t_Task::clear_has_tbxid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Task_t_Task::clear_tbxid() {
  tbxid_ = 0u;
  clear_has_tbxid();
}
inline ::google::protobuf::uint32 Task_t_Task::tbxid() const {
  return tbxid_;
}
inline void Task_t_Task::set_tbxid(::google::protobuf::uint32 value) {
  set_has_tbxid();
  tbxid_ = value;
}

// required uint32 id = 2;
inline bool Task_t_Task::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Task_t_Task::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Task_t_Task::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Task_t_Task::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 Task_t_Task::id() const {
  return id_;
}
inline void Task_t_Task::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required string title = 3;
inline bool Task_t_Task::has_title() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Task_t_Task::set_has_title() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Task_t_Task::clear_has_title() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Task_t_Task::clear_title() {
  if (title_ != &::google::protobuf::internal::kEmptyString) {
    title_->clear();
  }
  clear_has_title();
}
inline const ::std::string& Task_t_Task::title() const {
  return *title_;
}
inline void Task_t_Task::set_title(const ::std::string& value) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(value);
}
inline void Task_t_Task::set_title(const char* value) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(value);
}
inline void Task_t_Task::set_title(const char* value, size_t size) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Task_t_Task::mutable_title() {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  return title_;
}
inline ::std::string* Task_t_Task::release_title() {
  clear_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = title_;
    title_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Task_t_Task::set_allocated_title(::std::string* title) {
  if (title_ != &::google::protobuf::internal::kEmptyString) {
    delete title_;
  }
  if (title) {
    set_has_title();
    title_ = title;
  } else {
    clear_has_title();
    title_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string pre_id = 4;
inline bool Task_t_Task::has_pre_id() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Task_t_Task::set_has_pre_id() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Task_t_Task::clear_has_pre_id() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Task_t_Task::clear_pre_id() {
  if (pre_id_ != &::google::protobuf::internal::kEmptyString) {
    pre_id_->clear();
  }
  clear_has_pre_id();
}
inline const ::std::string& Task_t_Task::pre_id() const {
  return *pre_id_;
}
inline void Task_t_Task::set_pre_id(const ::std::string& value) {
  set_has_pre_id();
  if (pre_id_ == &::google::protobuf::internal::kEmptyString) {
    pre_id_ = new ::std::string;
  }
  pre_id_->assign(value);
}
inline void Task_t_Task::set_pre_id(const char* value) {
  set_has_pre_id();
  if (pre_id_ == &::google::protobuf::internal::kEmptyString) {
    pre_id_ = new ::std::string;
  }
  pre_id_->assign(value);
}
inline void Task_t_Task::set_pre_id(const char* value, size_t size) {
  set_has_pre_id();
  if (pre_id_ == &::google::protobuf::internal::kEmptyString) {
    pre_id_ = new ::std::string;
  }
  pre_id_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Task_t_Task::mutable_pre_id() {
  set_has_pre_id();
  if (pre_id_ == &::google::protobuf::internal::kEmptyString) {
    pre_id_ = new ::std::string;
  }
  return pre_id_;
}
inline ::std::string* Task_t_Task::release_pre_id() {
  clear_has_pre_id();
  if (pre_id_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = pre_id_;
    pre_id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Task_t_Task::set_allocated_pre_id(::std::string* pre_id) {
  if (pre_id_ != &::google::protobuf::internal::kEmptyString) {
    delete pre_id_;
  }
  if (pre_id) {
    set_has_pre_id();
    pre_id_ = pre_id;
  } else {
    clear_has_pre_id();
    pre_id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required uint32 sub = 5;
inline bool Task_t_Task::has_sub() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Task_t_Task::set_has_sub() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Task_t_Task::clear_has_sub() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Task_t_Task::clear_sub() {
  sub_ = 0u;
  clear_has_sub();
}
inline ::google::protobuf::uint32 Task_t_Task::sub() const {
  return sub_;
}
inline void Task_t_Task::set_sub(::google::protobuf::uint32 value) {
  set_has_sub();
  sub_ = value;
}

// required uint32 type = 6;
inline bool Task_t_Task::has_type() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Task_t_Task::set_has_type() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Task_t_Task::clear_has_type() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Task_t_Task::clear_type() {
  type_ = 0u;
  clear_has_type();
}
inline ::google::protobuf::uint32 Task_t_Task::type() const {
  return type_;
}
inline void Task_t_Task::set_type(::google::protobuf::uint32 value) {
  set_has_type();
  type_ = value;
}

// required uint32 pre_level = 7;
inline bool Task_t_Task::has_pre_level() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void Task_t_Task::set_has_pre_level() {
  _has_bits_[0] |= 0x00000040u;
}
inline void Task_t_Task::clear_has_pre_level() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void Task_t_Task::clear_pre_level() {
  pre_level_ = 0u;
  clear_has_pre_level();
}
inline ::google::protobuf::uint32 Task_t_Task::pre_level() const {
  return pre_level_;
}
inline void Task_t_Task::set_pre_level(::google::protobuf::uint32 value) {
  set_has_pre_level();
  pre_level_ = value;
}

// required uint32 target_type = 8;
inline bool Task_t_Task::has_target_type() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void Task_t_Task::set_has_target_type() {
  _has_bits_[0] |= 0x00000080u;
}
inline void Task_t_Task::clear_has_target_type() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void Task_t_Task::clear_target_type() {
  target_type_ = 0u;
  clear_has_target_type();
}
inline ::google::protobuf::uint32 Task_t_Task::target_type() const {
  return target_type_;
}
inline void Task_t_Task::set_target_type(::google::protobuf::uint32 value) {
  set_has_target_type();
  target_type_ = value;
}

// required string target = 9;
inline bool Task_t_Task::has_target() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void Task_t_Task::set_has_target() {
  _has_bits_[0] |= 0x00000100u;
}
inline void Task_t_Task::clear_has_target() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void Task_t_Task::clear_target() {
  if (target_ != &::google::protobuf::internal::kEmptyString) {
    target_->clear();
  }
  clear_has_target();
}
inline const ::std::string& Task_t_Task::target() const {
  return *target_;
}
inline void Task_t_Task::set_target(const ::std::string& value) {
  set_has_target();
  if (target_ == &::google::protobuf::internal::kEmptyString) {
    target_ = new ::std::string;
  }
  target_->assign(value);
}
inline void Task_t_Task::set_target(const char* value) {
  set_has_target();
  if (target_ == &::google::protobuf::internal::kEmptyString) {
    target_ = new ::std::string;
  }
  target_->assign(value);
}
inline void Task_t_Task::set_target(const char* value, size_t size) {
  set_has_target();
  if (target_ == &::google::protobuf::internal::kEmptyString) {
    target_ = new ::std::string;
  }
  target_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Task_t_Task::mutable_target() {
  set_has_target();
  if (target_ == &::google::protobuf::internal::kEmptyString) {
    target_ = new ::std::string;
  }
  return target_;
}
inline ::std::string* Task_t_Task::release_target() {
  clear_has_target();
  if (target_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = target_;
    target_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Task_t_Task::set_allocated_target(::std::string* target) {
  if (target_ != &::google::protobuf::internal::kEmptyString) {
    delete target_;
  }
  if (target) {
    set_has_target();
    target_ = target;
  } else {
    clear_has_target();
    target_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string target_content = 10;
inline bool Task_t_Task::has_target_content() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void Task_t_Task::set_has_target_content() {
  _has_bits_[0] |= 0x00000200u;
}
inline void Task_t_Task::clear_has_target_content() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void Task_t_Task::clear_target_content() {
  if (target_content_ != &::google::protobuf::internal::kEmptyString) {
    target_content_->clear();
  }
  clear_has_target_content();
}
inline const ::std::string& Task_t_Task::target_content() const {
  return *target_content_;
}
inline void Task_t_Task::set_target_content(const ::std::string& value) {
  set_has_target_content();
  if (target_content_ == &::google::protobuf::internal::kEmptyString) {
    target_content_ = new ::std::string;
  }
  target_content_->assign(value);
}
inline void Task_t_Task::set_target_content(const char* value) {
  set_has_target_content();
  if (target_content_ == &::google::protobuf::internal::kEmptyString) {
    target_content_ = new ::std::string;
  }
  target_content_->assign(value);
}
inline void Task_t_Task::set_target_content(const char* value, size_t size) {
  set_has_target_content();
  if (target_content_ == &::google::protobuf::internal::kEmptyString) {
    target_content_ = new ::std::string;
  }
  target_content_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Task_t_Task::mutable_target_content() {
  set_has_target_content();
  if (target_content_ == &::google::protobuf::internal::kEmptyString) {
    target_content_ = new ::std::string;
  }
  return target_content_;
}
inline ::std::string* Task_t_Task::release_target_content() {
  clear_has_target_content();
  if (target_content_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = target_content_;
    target_content_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Task_t_Task::set_allocated_target_content(::std::string* target_content) {
  if (target_content_ != &::google::protobuf::internal::kEmptyString) {
    delete target_content_;
  }
  if (target_content) {
    set_has_target_content();
    target_content_ = target_content;
  } else {
    clear_has_target_content();
    target_content_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string reward = 11;
inline bool Task_t_Task::has_reward() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void Task_t_Task::set_has_reward() {
  _has_bits_[0] |= 0x00000400u;
}
inline void Task_t_Task::clear_has_reward() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void Task_t_Task::clear_reward() {
  if (reward_ != &::google::protobuf::internal::kEmptyString) {
    reward_->clear();
  }
  clear_has_reward();
}
inline const ::std::string& Task_t_Task::reward() const {
  return *reward_;
}
inline void Task_t_Task::set_reward(const ::std::string& value) {
  set_has_reward();
  if (reward_ == &::google::protobuf::internal::kEmptyString) {
    reward_ = new ::std::string;
  }
  reward_->assign(value);
}
inline void Task_t_Task::set_reward(const char* value) {
  set_has_reward();
  if (reward_ == &::google::protobuf::internal::kEmptyString) {
    reward_ = new ::std::string;
  }
  reward_->assign(value);
}
inline void Task_t_Task::set_reward(const char* value, size_t size) {
  set_has_reward();
  if (reward_ == &::google::protobuf::internal::kEmptyString) {
    reward_ = new ::std::string;
  }
  reward_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Task_t_Task::mutable_reward() {
  set_has_reward();
  if (reward_ == &::google::protobuf::internal::kEmptyString) {
    reward_ = new ::std::string;
  }
  return reward_;
}
inline ::std::string* Task_t_Task::release_reward() {
  clear_has_reward();
  if (reward_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = reward_;
    reward_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Task_t_Task::set_allocated_reward(::std::string* reward) {
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

// required string icon = 12;
inline bool Task_t_Task::has_icon() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void Task_t_Task::set_has_icon() {
  _has_bits_[0] |= 0x00000800u;
}
inline void Task_t_Task::clear_has_icon() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void Task_t_Task::clear_icon() {
  if (icon_ != &::google::protobuf::internal::kEmptyString) {
    icon_->clear();
  }
  clear_has_icon();
}
inline const ::std::string& Task_t_Task::icon() const {
  return *icon_;
}
inline void Task_t_Task::set_icon(const ::std::string& value) {
  set_has_icon();
  if (icon_ == &::google::protobuf::internal::kEmptyString) {
    icon_ = new ::std::string;
  }
  icon_->assign(value);
}
inline void Task_t_Task::set_icon(const char* value) {
  set_has_icon();
  if (icon_ == &::google::protobuf::internal::kEmptyString) {
    icon_ = new ::std::string;
  }
  icon_->assign(value);
}
inline void Task_t_Task::set_icon(const char* value, size_t size) {
  set_has_icon();
  if (icon_ == &::google::protobuf::internal::kEmptyString) {
    icon_ = new ::std::string;
  }
  icon_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Task_t_Task::mutable_icon() {
  set_has_icon();
  if (icon_ == &::google::protobuf::internal::kEmptyString) {
    icon_ = new ::std::string;
  }
  return icon_;
}
inline ::std::string* Task_t_Task::release_icon() {
  clear_has_icon();
  if (icon_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = icon_;
    icon_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Task_t_Task::set_allocated_icon(::std::string* icon) {
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

// required uint32 guideType = 13;
inline bool Task_t_Task::has_guidetype() const {
  return (_has_bits_[0] & 0x00001000u) != 0;
}
inline void Task_t_Task::set_has_guidetype() {
  _has_bits_[0] |= 0x00001000u;
}
inline void Task_t_Task::clear_has_guidetype() {
  _has_bits_[0] &= ~0x00001000u;
}
inline void Task_t_Task::clear_guidetype() {
  guidetype_ = 0u;
  clear_has_guidetype();
}
inline ::google::protobuf::uint32 Task_t_Task::guidetype() const {
  return guidetype_;
}
inline void Task_t_Task::set_guidetype(::google::protobuf::uint32 value) {
  set_has_guidetype();
  guidetype_ = value;
}

// required string guideValue = 14;
inline bool Task_t_Task::has_guidevalue() const {
  return (_has_bits_[0] & 0x00002000u) != 0;
}
inline void Task_t_Task::set_has_guidevalue() {
  _has_bits_[0] |= 0x00002000u;
}
inline void Task_t_Task::clear_has_guidevalue() {
  _has_bits_[0] &= ~0x00002000u;
}
inline void Task_t_Task::clear_guidevalue() {
  if (guidevalue_ != &::google::protobuf::internal::kEmptyString) {
    guidevalue_->clear();
  }
  clear_has_guidevalue();
}
inline const ::std::string& Task_t_Task::guidevalue() const {
  return *guidevalue_;
}
inline void Task_t_Task::set_guidevalue(const ::std::string& value) {
  set_has_guidevalue();
  if (guidevalue_ == &::google::protobuf::internal::kEmptyString) {
    guidevalue_ = new ::std::string;
  }
  guidevalue_->assign(value);
}
inline void Task_t_Task::set_guidevalue(const char* value) {
  set_has_guidevalue();
  if (guidevalue_ == &::google::protobuf::internal::kEmptyString) {
    guidevalue_ = new ::std::string;
  }
  guidevalue_->assign(value);
}
inline void Task_t_Task::set_guidevalue(const char* value, size_t size) {
  set_has_guidevalue();
  if (guidevalue_ == &::google::protobuf::internal::kEmptyString) {
    guidevalue_ = new ::std::string;
  }
  guidevalue_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Task_t_Task::mutable_guidevalue() {
  set_has_guidevalue();
  if (guidevalue_ == &::google::protobuf::internal::kEmptyString) {
    guidevalue_ = new ::std::string;
  }
  return guidevalue_;
}
inline ::std::string* Task_t_Task::release_guidevalue() {
  clear_has_guidevalue();
  if (guidevalue_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = guidevalue_;
    guidevalue_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Task_t_Task::set_allocated_guidevalue(::std::string* guidevalue) {
  if (guidevalue_ != &::google::protobuf::internal::kEmptyString) {
    delete guidevalue_;
  }
  if (guidevalue) {
    set_has_guidevalue();
    guidevalue_ = guidevalue;
  } else {
    clear_has_guidevalue();
    guidevalue_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// Task

// repeated .pb.Task.t_Task datas = 1;
inline int Task::datas_size() const {
  return datas_.size();
}
inline void Task::clear_datas() {
  datas_.Clear();
}
inline const ::pb::Task_t_Task& Task::datas(int index) const {
  return datas_.Get(index);
}
inline ::pb::Task_t_Task* Task::mutable_datas(int index) {
  return datas_.Mutable(index);
}
inline ::pb::Task_t_Task* Task::add_datas() {
  return datas_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::Task_t_Task >&
Task::datas() const {
  return datas_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::Task_t_Task >*
Task::mutable_datas() {
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

#endif  // PROTOBUF_TaskInfo_2eproto__INCLUDED
