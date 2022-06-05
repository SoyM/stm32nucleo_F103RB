# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: User/demo.proto
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x0fUser/demo.proto\x12\x06people\"\x89\x02\n\x06Person\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\n\n\x02id\x18\x02 \x01(\x05\x12%\n\x06gender\x18\x03 \x01(\x0e\x32\x15.people.Person.Gender\x12*\n\x06phones\x18\x04 \x03(\x0b\x32\x1a.people.Person.PhoneNumber\x1a\x45\n\x0bPhoneNumber\x12\x0e\n\x06number\x18\x01 \x01(\t\x12&\n\x04type\x18\x02 \x01(\x0e\x32\x18.people.Person.PhoneType\"\x1e\n\x06Gender\x12\n\n\x06\x46\x45MALE\x10\x00\x12\x08\n\x04MALE\x10\x01\"+\n\tPhoneType\x12\n\n\x06MOBILE\x10\x00\x12\x08\n\x04HOME\x10\x01\x12\x08\n\x04WORK\x10\x02\x62\x06proto3')



_PERSON = DESCRIPTOR.message_types_by_name['Person']
_PERSON_PHONENUMBER = _PERSON.nested_types_by_name['PhoneNumber']
_PERSON_GENDER = _PERSON.enum_types_by_name['Gender']
_PERSON_PHONETYPE = _PERSON.enum_types_by_name['PhoneType']
Person = _reflection.GeneratedProtocolMessageType('Person', (_message.Message,), {

  'PhoneNumber' : _reflection.GeneratedProtocolMessageType('PhoneNumber', (_message.Message,), {
    'DESCRIPTOR' : _PERSON_PHONENUMBER,
    '__module__' : 'User.demo_pb2'
    # @@protoc_insertion_point(class_scope:people.Person.PhoneNumber)
    })
  ,
  'DESCRIPTOR' : _PERSON,
  '__module__' : 'User.demo_pb2'
  # @@protoc_insertion_point(class_scope:people.Person)
  })
_sym_db.RegisterMessage(Person)
_sym_db.RegisterMessage(Person.PhoneNumber)

if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _PERSON._serialized_start=28
  _PERSON._serialized_end=293
  _PERSON_PHONENUMBER._serialized_start=147
  _PERSON_PHONENUMBER._serialized_end=216
  _PERSON_GENDER._serialized_start=218
  _PERSON_GENDER._serialized_end=248
  _PERSON_PHONETYPE._serialized_start=250
  _PERSON_PHONETYPE._serialized_end=293
# @@protoc_insertion_point(module_scope)
