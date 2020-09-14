// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MetaInfo.proto

#ifndef PROTOBUF_INCLUDED_MetaInfo_2eproto
#define PROTOBUF_INCLUDED_MetaInfo_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include "DirectoryEntryMessage.pb.h"
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_MetaInfo_2eproto 

namespace protobuf_MetaInfo_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_MetaInfo_2eproto
class WorkspaceMetaInfo;
class WorkspaceMetaInfoDefaultTypeInternal;
extern WorkspaceMetaInfoDefaultTypeInternal _WorkspaceMetaInfo_default_instance_;
namespace google {
namespace protobuf {
template<> ::WorkspaceMetaInfo* Arena::CreateMaybeMessage<::WorkspaceMetaInfo>(Arena*);
}  // namespace protobuf
}  // namespace google

enum WorkspaceMetaInfo_Status {
  WorkspaceMetaInfo_Status_OK = 0,
  WorkspaceMetaInfo_Status_NEW_DIRECTORY = 1,
  WorkspaceMetaInfo_Status_FAIL = 2
};
bool WorkspaceMetaInfo_Status_IsValid(int value);
const WorkspaceMetaInfo_Status WorkspaceMetaInfo_Status_Status_MIN = WorkspaceMetaInfo_Status_OK;
const WorkspaceMetaInfo_Status WorkspaceMetaInfo_Status_Status_MAX = WorkspaceMetaInfo_Status_FAIL;
const int WorkspaceMetaInfo_Status_Status_ARRAYSIZE = WorkspaceMetaInfo_Status_Status_MAX + 1;

const ::google::protobuf::EnumDescriptor* WorkspaceMetaInfo_Status_descriptor();
inline const ::std::string& WorkspaceMetaInfo_Status_Name(WorkspaceMetaInfo_Status value) {
  return ::google::protobuf::internal::NameOfEnum(
    WorkspaceMetaInfo_Status_descriptor(), value);
}
inline bool WorkspaceMetaInfo_Status_Parse(
    const ::std::string& name, WorkspaceMetaInfo_Status* value) {
  return ::google::protobuf::internal::ParseNamedEnum<WorkspaceMetaInfo_Status>(
    WorkspaceMetaInfo_Status_descriptor(), name, value);
}
// ===================================================================

class WorkspaceMetaInfo : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:WorkspaceMetaInfo) */ {
 public:
  WorkspaceMetaInfo();
  virtual ~WorkspaceMetaInfo();

  WorkspaceMetaInfo(const WorkspaceMetaInfo& from);

  inline WorkspaceMetaInfo& operator=(const WorkspaceMetaInfo& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  WorkspaceMetaInfo(WorkspaceMetaInfo&& from) noexcept
    : WorkspaceMetaInfo() {
    *this = ::std::move(from);
  }

  inline WorkspaceMetaInfo& operator=(WorkspaceMetaInfo&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const WorkspaceMetaInfo& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const WorkspaceMetaInfo* internal_default_instance() {
    return reinterpret_cast<const WorkspaceMetaInfo*>(
               &_WorkspaceMetaInfo_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(WorkspaceMetaInfo* other);
  friend void swap(WorkspaceMetaInfo& a, WorkspaceMetaInfo& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline WorkspaceMetaInfo* New() const final {
    return CreateMaybeMessage<WorkspaceMetaInfo>(NULL);
  }

  WorkspaceMetaInfo* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<WorkspaceMetaInfo>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const WorkspaceMetaInfo& from);
  void MergeFrom(const WorkspaceMetaInfo& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(WorkspaceMetaInfo* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  typedef WorkspaceMetaInfo_Status Status;
  static const Status OK =
    WorkspaceMetaInfo_Status_OK;
  static const Status NEW_DIRECTORY =
    WorkspaceMetaInfo_Status_NEW_DIRECTORY;
  static const Status FAIL =
    WorkspaceMetaInfo_Status_FAIL;
  static inline bool Status_IsValid(int value) {
    return WorkspaceMetaInfo_Status_IsValid(value);
  }
  static const Status Status_MIN =
    WorkspaceMetaInfo_Status_Status_MIN;
  static const Status Status_MAX =
    WorkspaceMetaInfo_Status_Status_MAX;
  static const int Status_ARRAYSIZE =
    WorkspaceMetaInfo_Status_Status_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Status_descriptor() {
    return WorkspaceMetaInfo_Status_descriptor();
  }
  static inline const ::std::string& Status_Name(Status value) {
    return WorkspaceMetaInfo_Status_Name(value);
  }
  static inline bool Status_Parse(const ::std::string& name,
      Status* value) {
    return WorkspaceMetaInfo_Status_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // repeated .DirectoryEntryMessage list = 2;
  int list_size() const;
  void clear_list();
  static const int kListFieldNumber = 2;
  ::DirectoryEntryMessage* mutable_list(int index);
  ::google::protobuf::RepeatedPtrField< ::DirectoryEntryMessage >*
      mutable_list();
  const ::DirectoryEntryMessage& list(int index) const;
  ::DirectoryEntryMessage* add_list();
  const ::google::protobuf::RepeatedPtrField< ::DirectoryEntryMessage >&
      list() const;

  // required .WorkspaceMetaInfo.Status status = 1;
  bool has_status() const;
  void clear_status();
  static const int kStatusFieldNumber = 1;
  ::WorkspaceMetaInfo_Status status() const;
  void set_status(::WorkspaceMetaInfo_Status value);

  // @@protoc_insertion_point(class_scope:WorkspaceMetaInfo)
 private:
  void set_has_status();
  void clear_has_status();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::DirectoryEntryMessage > list_;
  int status_;
  friend struct ::protobuf_MetaInfo_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// WorkspaceMetaInfo

// required .WorkspaceMetaInfo.Status status = 1;
inline bool WorkspaceMetaInfo::has_status() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void WorkspaceMetaInfo::set_has_status() {
  _has_bits_[0] |= 0x00000001u;
}
inline void WorkspaceMetaInfo::clear_has_status() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void WorkspaceMetaInfo::clear_status() {
  status_ = 0;
  clear_has_status();
}
inline ::WorkspaceMetaInfo_Status WorkspaceMetaInfo::status() const {
  // @@protoc_insertion_point(field_get:WorkspaceMetaInfo.status)
  return static_cast< ::WorkspaceMetaInfo_Status >(status_);
}
inline void WorkspaceMetaInfo::set_status(::WorkspaceMetaInfo_Status value) {
  assert(::WorkspaceMetaInfo_Status_IsValid(value));
  set_has_status();
  status_ = value;
  // @@protoc_insertion_point(field_set:WorkspaceMetaInfo.status)
}

// repeated .DirectoryEntryMessage list = 2;
inline int WorkspaceMetaInfo::list_size() const {
  return list_.size();
}
inline ::DirectoryEntryMessage* WorkspaceMetaInfo::mutable_list(int index) {
  // @@protoc_insertion_point(field_mutable:WorkspaceMetaInfo.list)
  return list_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::DirectoryEntryMessage >*
WorkspaceMetaInfo::mutable_list() {
  // @@protoc_insertion_point(field_mutable_list:WorkspaceMetaInfo.list)
  return &list_;
}
inline const ::DirectoryEntryMessage& WorkspaceMetaInfo::list(int index) const {
  // @@protoc_insertion_point(field_get:WorkspaceMetaInfo.list)
  return list_.Get(index);
}
inline ::DirectoryEntryMessage* WorkspaceMetaInfo::add_list() {
  // @@protoc_insertion_point(field_add:WorkspaceMetaInfo.list)
  return list_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::DirectoryEntryMessage >&
WorkspaceMetaInfo::list() const {
  // @@protoc_insertion_point(field_list:WorkspaceMetaInfo.list)
  return list_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::WorkspaceMetaInfo_Status> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::WorkspaceMetaInfo_Status>() {
  return ::WorkspaceMetaInfo_Status_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_MetaInfo_2eproto