# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: buildDepends.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='buildDepends.proto',
  package='pb',
  serialized_pb='\n\x12\x62uildDepends.proto\x12\x02pb\"\x87\x01\n\x0c\x62uildDepends\x12.\n\x05\x64\x61tas\x18\x01 \x03(\x0b\x32\x1f.pb.buildDepends.t_buildDepends\x1aG\n\x0et_buildDepends\x12\r\n\x05tbxid\x18\x01 \x02(\r\x12\n\n\x02id\x18\x02 \x02(\t\x12\x0c\n\x04name\x18\x03 \x02(\t\x12\x0c\n\x04info\x18\x04 \x02(\t')




_BUILDDEPENDS_T_BUILDDEPENDS = _descriptor.Descriptor(
  name='t_buildDepends',
  full_name='pb.buildDepends.t_buildDepends',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='tbxid', full_name='pb.buildDepends.t_buildDepends.tbxid', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='id', full_name='pb.buildDepends.t_buildDepends.id', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='name', full_name='pb.buildDepends.t_buildDepends.name', index=2,
      number=3, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='info', full_name='pb.buildDepends.t_buildDepends.info', index=3,
      number=4, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
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
  serialized_start=91,
  serialized_end=162,
)

_BUILDDEPENDS = _descriptor.Descriptor(
  name='buildDepends',
  full_name='pb.buildDepends',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='datas', full_name='pb.buildDepends.datas', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[_BUILDDEPENDS_T_BUILDDEPENDS, ],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=27,
  serialized_end=162,
)

_BUILDDEPENDS_T_BUILDDEPENDS.containing_type = _BUILDDEPENDS;
_BUILDDEPENDS.fields_by_name['datas'].message_type = _BUILDDEPENDS_T_BUILDDEPENDS
DESCRIPTOR.message_types_by_name['buildDepends'] = _BUILDDEPENDS

class buildDepends(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType

  class t_buildDepends(_message.Message):
    __metaclass__ = _reflection.GeneratedProtocolMessageType
    DESCRIPTOR = _BUILDDEPENDS_T_BUILDDEPENDS

    # @@protoc_insertion_point(class_scope:pb.buildDepends.t_buildDepends)
  DESCRIPTOR = _BUILDDEPENDS

  # @@protoc_insertion_point(class_scope:pb.buildDepends)


# @@protoc_insertion_point(module_scope)