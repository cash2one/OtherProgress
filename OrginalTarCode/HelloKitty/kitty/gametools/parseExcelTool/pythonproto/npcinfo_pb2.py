# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: npcinfo.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='npcinfo.proto',
  package='pb',
  serialized_pb='\n\rnpcinfo.proto\x12\x02pb\"\x88\x02\n\x07npcinfo\x12$\n\x05\x64\x61tas\x18\x01 \x03(\x0b\x32\x15.pb.npcinfo.t_npcinfo\x1a\xd6\x01\n\tt_npcinfo\x12\r\n\x05tbxid\x18\x01 \x02(\r\x12\n\n\x02id\x18\x02 \x02(\r\x12\x0c\n\x04name\x18\x03 \x02(\t\x12\x0b\n\x03pic\x18\x04 \x02(\r\x12\x0e\n\x06getWay\x18\x05 \x02(\r\x12\x10\n\x08\x66unction\x18\x06 \x02(\r\x12\x15\n\rfunctionValue\x18\x07 \x02(\r\x12\x10\n\x08\x66riendly\x18\x08 \x02(\r\x12\x0f\n\x07require\x18\t \x02(\r\x12\x16\n\x0emissionRequire\x18\n \x02(\r\x12\r\n\x05grade\x18\x0b \x02(\r\x12\x10\n\x08\x64\x65scribe\x18\x0c \x02(\r')




_NPCINFO_T_NPCINFO = _descriptor.Descriptor(
  name='t_npcinfo',
  full_name='pb.npcinfo.t_npcinfo',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='tbxid', full_name='pb.npcinfo.t_npcinfo.tbxid', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='id', full_name='pb.npcinfo.t_npcinfo.id', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='name', full_name='pb.npcinfo.t_npcinfo.name', index=2,
      number=3, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='pic', full_name='pb.npcinfo.t_npcinfo.pic', index=3,
      number=4, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='getWay', full_name='pb.npcinfo.t_npcinfo.getWay', index=4,
      number=5, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='function', full_name='pb.npcinfo.t_npcinfo.function', index=5,
      number=6, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='functionValue', full_name='pb.npcinfo.t_npcinfo.functionValue', index=6,
      number=7, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='friendly', full_name='pb.npcinfo.t_npcinfo.friendly', index=7,
      number=8, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='require', full_name='pb.npcinfo.t_npcinfo.require', index=8,
      number=9, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='missionRequire', full_name='pb.npcinfo.t_npcinfo.missionRequire', index=9,
      number=10, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='grade', full_name='pb.npcinfo.t_npcinfo.grade', index=10,
      number=11, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='describe', full_name='pb.npcinfo.t_npcinfo.describe', index=11,
      number=12, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=72,
  serialized_end=286,
)

_NPCINFO = _descriptor.Descriptor(
  name='npcinfo',
  full_name='pb.npcinfo',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='datas', full_name='pb.npcinfo.datas', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[_NPCINFO_T_NPCINFO, ],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=22,
  serialized_end=286,
)

_NPCINFO_T_NPCINFO.containing_type = _NPCINFO;
_NPCINFO.fields_by_name['datas'].message_type = _NPCINFO_T_NPCINFO
DESCRIPTOR.message_types_by_name['npcinfo'] = _NPCINFO

class npcinfo(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType

  class t_npcinfo(_message.Message):
    __metaclass__ = _reflection.GeneratedProtocolMessageType
    DESCRIPTOR = _NPCINFO_T_NPCINFO

    # @@protoc_insertion_point(class_scope:pb.npcinfo.t_npcinfo)
  DESCRIPTOR = _NPCINFO

  # @@protoc_insertion_point(class_scope:pb.npcinfo)


# @@protoc_insertion_point(module_scope)