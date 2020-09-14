// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: JobResponse.proto

#ifndef PROTOBUF_INCLUDED_JobResponse_2eproto
#define PROTOBUF_INCLUDED_JobResponse_2eproto

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
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_JobResponse_2eproto 

namespace protobuf_JobResponse_2eproto {
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
}  // namespace protobuf_JobResponse_2eproto
class JobResponse;
class JobResponseDefaultTypeInternal;
extern JobResponseDefaultTypeInternal _JobResponse_default_instance_;
namespace google {
namespace protobuf {
template<> ::JobResponse* Arena::CreateMaybeMessage<::JobResponse>(Arena*);
}  // namespace protobuf
}  // namespace google

enum JobResponse_Status {
  JobResponse_Status_OK = 0,
  JobResponse_Status_FAIL = 1
};
bool JobResponse_Status_IsValid(int value);
const JobResponse_Status JobResponse_Status_Status_MIN = JobResponse_Status_OK;
const JobResponse_Status JobResponse_Status_Status_MAX = JobResponse_Status_FAIL;
const int JobResponse_Status_Status_ARRAYSIZE = JobResponse_Status_Status_MAX + 1;

const ::google::protobuf::EnumDescriptor* JobResponse_Status_descriptor();
inline const ::std::string& JobResponse_Status_Name(JobResponse_Status value) {
  return ::google::protobuf::internal::NameOfEnum(
    JobResponse_Status_descriptor(), value);
}
inline bool JobResponse_Status_Parse(
    const ::std::string& name, JobResponse_Status* value) {
  return ::google::protobuf::internal::ParseNamedEnum<JobResponse_Status>(
    JobResponse_Status_descriptor(), name, value);
}
// ===================================================================

class JobResponse : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:JobResponse) */ {
 public:
  JobResponse();
  virtual ~JobResponse();

  JobResponse(const JobResponse& from);

  inline JobResponse& operator=(const JobResponse& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  JobResponse(JobResponse&& from) noexcept
    : JobResponse() {
    *this = ::std::move(from);
  }

  inline JobResponse& operator=(JobResponse&& from) noexcept {
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
  static const JobResponse& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const JobResponse* internal_default_instance() {
    return reinterpret_cast<const JobResponse*>(
               &_JobResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(JobResponse* other);
  friend void swap(JobResponse& a, JobResponse& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline JobResponse* New() const final {
    return CreateMaybeMessage<JobResponse>(NULL);
  }

  JobResponse* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<JobResponse>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const JobResponse& from);
  void MergeFrom(const JobResponse& from);
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
  void InternalSwap(JobResponse* other);
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

  typedef JobResponse_Status Status;
  static const Status OK =
    JobResponse_Status_OK;
  static const Status FAIL =
    JobResponse_Status_FAIL;
  static inline bool Status_IsValid(int value) {
    return JobResponse_Status_IsValid(value);
  }
  static const Status Status_MIN =
    JobResponse_Status_Status_MIN;
  static const Status Status_MAX =
    JobResponse_Status_Status_MAX;
  static const int Status_ARRAYSIZE =
    JobResponse_Status_Status_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Status_descriptor() {
    return JobResponse_Status_descriptor();
  }
  static inline const ::std::string& Status_Name(Status value) {
    return JobResponse_Status_Name(value);
  }
  static inline bool Status_Parse(const ::std::string& name,
      Status* value) {
    return JobResponse_Status_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required string path = 2;
  bool has_path() const;
  void clear_path();
  static const int kPathFieldNumber = 2;
  const ::std::string& path() const;
  void set_path(const ::std::string& value);
  #if LANG_CXX11
  void set_path(::std::string&& value);
  #endif
  void set_path(const char* value);
  void set_path(const char* value, size_t size);
  ::std::string* mutable_path();
  ::std::string* release_path();
  void set_allocated_path(::std::string* path);

  // optional string checksum = 3;
  bool has_checksum() const;
  void clear_checksum();
  static const int kChecksumFieldNumber = 3;
  const ::std::string& checksum() const;
  void set_checksum(const ::std::string& value);
  #if LANG_CXX11
  void set_checksum(::std::string&& value);
  #endif
  void set_checksum(const char* value);
  void set_checksum(const char* value, size_t size);
  ::std::string* mutable_checksum();
  ::std::string* release_checksum();
  void set_allocated_checksum(::std::string* checksum);

  // required .JobResponse.Status status = 1;
  bool has_status() const;
  void clear_status();
  static const int kStatusFieldNumber = 1;
  ::JobResponse_Status status() const;
  void set_status(::JobResponse_Status value);

  // @@protoc_insertion_point(class_scope:JobResponse)
 private:
  void set_has_path();
  void clear_has_path();
  void set_has_status();
  void clear_has_status();
  void set_has_checksum();
  void clear_has_checksum();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr path_;
  ::google::protobuf::internal::ArenaStringPtr checksum_;
  int status_;
  friend struct ::protobuf_JobResponse_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// JobResponse

// required string path = 2;
inline bool JobResponse::has_path() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void JobResponse::set_has_path() {
  _has_bits_[0] |= 0x00000001u;
}
inline void JobResponse::clear_has_path() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void JobResponse::clear_path() {
  path_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_path();
}
inline const ::std::string& JobResponse::path() const {
  // @@protoc_insertion_point(field_get:JobResponse.path)
  return path_.GetNoArena();
}
inline void JobResponse::set_path(const ::std::string& value) {
  set_has_path();
  path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:JobResponse.path)
}
#if LANG_CXX11
inline void JobResponse::set_path(::std::string&& value) {
  set_has_path();
  path_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:JobResponse.path)
}
#endif
inline void JobResponse::set_path(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_path();
  path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:JobResponse.path)
}
inline void JobResponse::set_path(const char* value, size_t size) {
  set_has_path();
  path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:JobResponse.path)
}
inline ::std::string* JobResponse::mutable_path() {
  set_has_path();
  // @@protoc_insertion_point(field_mutable:JobResponse.path)
  return path_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* JobResponse::release_path() {
  // @@protoc_insertion_point(field_release:JobResponse.path)
  if (!has_path()) {
    return NULL;
  }
  clear_has_path();
  return path_.ReleaseNonDefaultNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void JobResponse::set_allocated_path(::std::string* path) {
  if (path != NULL) {
    set_has_path();
  } else {
    clear_has_path();
  }
  path_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), path);
  // @@protoc_insertion_point(field_set_allocated:JobResponse.path)
}

// required .JobResponse.Status status = 1;
inline bool JobResponse::has_status() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void JobResponse::set_has_status() {
  _has_bits_[0] |= 0x00000004u;
}
inline void JobResponse::clear_has_status() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void JobResponse::clear_status() {
  status_ = 0;
  clear_has_status();
}
inline ::JobResponse_Status JobResponse::status() const {
  // @@protoc_insertion_point(field_get:JobResponse.status)
  return static_cast< ::JobResponse_Status >(status_);
}
inline void JobResponse::set_status(::JobResponse_Status value) {
  assert(::JobResponse_Status_IsValid(value));
  set_has_status();
  status_ = value;
  // @@protoc_insertion_point(field_set:JobResponse.status)
}

// optional string checksum = 3;
inline bool JobResponse::has_checksum() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void JobResponse::set_has_checksum() {
  _has_bits_[0] |= 0x00000002u;
}
inline void JobResponse::clear_has_checksum() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void JobResponse::clear_checksum() {
  checksum_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_checksum();
}
inline const ::std::string& JobResponse::checksum() const {
  // @@protoc_insertion_point(field_get:JobResponse.checksum)
  return checksum_.GetNoArena();
}
inline void JobResponse::set_checksum(const ::std::string& value) {
  set_has_checksum();
  checksum_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:JobResponse.checksum)
}
#if LANG_CXX11
inline void JobResponse::set_checksum(::std::string&& value) {
  set_has_checksum();
  checksum_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:JobResponse.checksum)
}
#endif
inline void JobResponse::set_checksum(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_checksum();
  checksum_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:JobResponse.checksum)
}
inline void JobResponse::set_checksum(const char* value, size_t size) {
  set_has_checksum();
  checksum_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:JobResponse.checksum)
}
inline ::std::string* JobResponse::mutable_checksum() {
  set_has_checksum();
  // @@protoc_insertion_point(field_mutable:JobResponse.checksum)
  return checksum_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* JobResponse::release_checksum() {
  // @@protoc_insertion_point(field_release:JobResponse.checksum)
  if (!has_checksum()) {
    return NULL;
  }
  clear_has_checksum();
  return checksum_.ReleaseNonDefaultNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void JobResponse::set_allocated_checksum(::std::string* checksum) {
  if (checksum != NULL) {
    set_has_checksum();
  } else {
    clear_has_checksum();
  }
  checksum_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), checksum);
  // @@protoc_insertion_point(field_set_allocated:JobResponse.checksum)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::JobResponse_Status> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::JobResponse_Status>() {
  return ::JobResponse_Status_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_JobResponse_2eproto
