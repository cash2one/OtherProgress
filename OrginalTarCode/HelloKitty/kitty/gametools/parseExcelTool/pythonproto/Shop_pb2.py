# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: Shop.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='Shop.proto',
  package='pb',
  serialized_pb='\n\nShop.proto\x12\x02pb\"\xb7\x01\n\x04Shop\x12\x1e\n\x05\x64\x61tas\x18\x01 \x03(\x0b\x32\x0f.pb.Shop.t_Shop\x1a\x8e\x01\n\x06t_Shop\x12\r\n\x05tbxid\x18\x01 \x02(\r\x12\n\n\x02id\x18\x02 \x02(\r\x12\r\n\x05mtype\x18\x03 \x02(\r\x12\x0e\n\x06itemid\x18\x04 \x02(\r\x12\r\n\x05stype\x18\x05 \x02(\r\x12\r\n\x05\x63type\x18\x06 \x02(\r\x12\r\n\x05price\x18\x07 \x02(\r\x12\x10\n\x08\x64isPrice\x18\x08 \x02(\r\x12\x0b\n\x03max\x18\t \x02(\r')




_SHOP_T_SHOP = _descriptor.Descriptor(
  name='t_Shop',
  full_name='pb.Shop.t_Shop',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='tbxid', full_name='pb.Shop.t_Shop.tbxid', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='id', full_name='pb.Shop.t_Shop.id', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='mtype', full_name='pb.Shop.t_Shop.mtype', index=2,
      number=3, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='itemid', full_name='pb.Shop.t_Shop.itemid', index=3,
      number=4, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='stype', full_name='pb.Shop.t_Shop.stype', index=4,
      number=5, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ctype', full_name='pb.Shop.t_Shop.ctype', index=5,
      number=6, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='price', full_name='pb.Shop.t_Shop.price', index=6,
      number=7, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='disPrice', full_name='pb.Shop.t_Shop.disPrice', index=7,
      number=8, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='max', full_name='pb.Shop.t_Shop.max', index=8,
      number=9, type=13, cpp_type=3, label=2,
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
  serialized_start=60,
  serialized_end=202,
)

_SHOP = _descriptor.Descriptor(
  name='Shop',
  full_name='pb.Shop',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='datas', full_name='pb.Shop.datas', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[_SHOP_T_SHOP, ],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=19,
  serialized_end=202,
)

_SHOP_T_SHOP.containing_type = _SHOP;
_SHOP.fields_by_name['datas'].message_type = _SHOP_T_SHOP
DESCRIPTOR.message_types_by_name['Shop'] = _SHOP

class Shop(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType

  class t_Shop(_message.Message):
    __metaclass__ = _reflection.GeneratedProtocolMessageType
    DESCRIPTOR = _SHOP_T_SHOP

    # @@protoc_insertion_point(class_scope:pb.Shop.t_Shop)
  DESCRIPTOR = _SHOP

  # @@protoc_insertion_point(class_scope:pb.Shop)


# @@protoc_insertion_point(module_scope)
