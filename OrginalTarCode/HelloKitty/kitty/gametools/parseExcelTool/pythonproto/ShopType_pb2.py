# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ShopType.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='ShopType.proto',
  package='pb',
  serialized_pb='\n\x0eShopType.proto\x12\x02pb\"\xa6\x01\n\x08ShopType\x12&\n\x05\x64\x61tas\x18\x01 \x03(\x0b\x32\x17.pb.ShopType.t_ShopType\x1ar\n\nt_ShopType\x12\r\n\x05tbxid\x18\x01 \x02(\r\x12\n\n\x02id\x18\x02 \x02(\r\x12\r\n\x05order\x18\x03 \x02(\r\x12\x0c\n\x04icon\x18\x04 \x02(\t\x12\x0c\n\x04name\x18\x05 \x02(\t\x12\x0c\n\x04open\x18\x06 \x02(\r\x12\x10\n\x08minLevel\x18\x07 \x02(\r')




_SHOPTYPE_T_SHOPTYPE = _descriptor.Descriptor(
  name='t_ShopType',
  full_name='pb.ShopType.t_ShopType',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='tbxid', full_name='pb.ShopType.t_ShopType.tbxid', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='id', full_name='pb.ShopType.t_ShopType.id', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='order', full_name='pb.ShopType.t_ShopType.order', index=2,
      number=3, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='icon', full_name='pb.ShopType.t_ShopType.icon', index=3,
      number=4, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='name', full_name='pb.ShopType.t_ShopType.name', index=4,
      number=5, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='open', full_name='pb.ShopType.t_ShopType.open', index=5,
      number=6, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='minLevel', full_name='pb.ShopType.t_ShopType.minLevel', index=6,
      number=7, type=13, cpp_type=3, label=2,
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
  serialized_start=75,
  serialized_end=189,
)

_SHOPTYPE = _descriptor.Descriptor(
  name='ShopType',
  full_name='pb.ShopType',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='datas', full_name='pb.ShopType.datas', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[_SHOPTYPE_T_SHOPTYPE, ],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=23,
  serialized_end=189,
)

_SHOPTYPE_T_SHOPTYPE.containing_type = _SHOPTYPE;
_SHOPTYPE.fields_by_name['datas'].message_type = _SHOPTYPE_T_SHOPTYPE
DESCRIPTOR.message_types_by_name['ShopType'] = _SHOPTYPE

class ShopType(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType

  class t_ShopType(_message.Message):
    __metaclass__ = _reflection.GeneratedProtocolMessageType
    DESCRIPTOR = _SHOPTYPE_T_SHOPTYPE

    # @@protoc_insertion_point(class_scope:pb.ShopType.t_ShopType)
  DESCRIPTOR = _SHOPTYPE

  # @@protoc_insertion_point(class_scope:pb.ShopType)


# @@protoc_insertion_point(module_scope)
