// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AvailableWorkspaces.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_AvailableWorkspaces_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_AvailableWorkspaces_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 4000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 4000000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_AvailableWorkspaces_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_AvailableWorkspaces_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_AvailableWorkspaces_2eproto;
class AvailableWorkspaces;
class AvailableWorkspacesDefaultTypeInternal;
extern AvailableWorkspacesDefaultTypeInternal _AvailableWorkspaces_default_instance_;
class AvailableWorkspaces_MachinePath;
class AvailableWorkspaces_MachinePathDefaultTypeInternal;
extern AvailableWorkspaces_MachinePathDefaultTypeInternal _AvailableWorkspaces_MachinePath_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::AvailableWorkspaces* Arena::CreateMaybeMessage<::AvailableWorkspaces>(Arena*);
template<> ::AvailableWorkspaces_MachinePath* Arena::CreateMaybeMessage<::AvailableWorkspaces_MachinePath>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

enum AvailableWorkspaces_Status : int {
  AvailableWorkspaces_Status_OK = 0,
  AvailableWorkspaces_Status_FAIL = 1
};
bool AvailableWorkspaces_Status_IsValid(int value);
constexpr AvailableWorkspaces_Status AvailableWorkspaces_Status_Status_MIN = AvailableWorkspaces_Status_OK;
constexpr AvailableWorkspaces_Status AvailableWorkspaces_Status_Status_MAX = AvailableWorkspaces_Status_FAIL;
constexpr int AvailableWorkspaces_Status_Status_ARRAYSIZE = AvailableWorkspaces_Status_Status_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* AvailableWorkspaces_Status_descriptor();
template<typename T>
inline const std::string& AvailableWorkspaces_Status_Name(T enum_t_value) {
  static_assert(::std::is_same<T, AvailableWorkspaces_Status>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function AvailableWorkspaces_Status_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    AvailableWorkspaces_Status_descriptor(), enum_t_value);
}
inline bool AvailableWorkspaces_Status_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, AvailableWorkspaces_Status* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<AvailableWorkspaces_Status>(
    AvailableWorkspaces_Status_descriptor(), name, value);
}
// ===================================================================

class AvailableWorkspaces_MachinePath PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:AvailableWorkspaces.MachinePath) */ {
 public:
  inline AvailableWorkspaces_MachinePath() : AvailableWorkspaces_MachinePath(nullptr) {}
  virtual ~AvailableWorkspaces_MachinePath();

  AvailableWorkspaces_MachinePath(const AvailableWorkspaces_MachinePath& from);
  AvailableWorkspaces_MachinePath(AvailableWorkspaces_MachinePath&& from) noexcept
    : AvailableWorkspaces_MachinePath() {
    *this = ::std::move(from);
  }

  inline AvailableWorkspaces_MachinePath& operator=(const AvailableWorkspaces_MachinePath& from) {
    CopyFrom(from);
    return *this;
  }
  inline AvailableWorkspaces_MachinePath& operator=(AvailableWorkspaces_MachinePath&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const AvailableWorkspaces_MachinePath& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const AvailableWorkspaces_MachinePath* internal_default_instance() {
    return reinterpret_cast<const AvailableWorkspaces_MachinePath*>(
               &_AvailableWorkspaces_MachinePath_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(AvailableWorkspaces_MachinePath& a, AvailableWorkspaces_MachinePath& b) {
    a.Swap(&b);
  }
  inline void Swap(AvailableWorkspaces_MachinePath* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(AvailableWorkspaces_MachinePath* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline AvailableWorkspaces_MachinePath* New() const final {
    return CreateMaybeMessage<AvailableWorkspaces_MachinePath>(nullptr);
  }

  AvailableWorkspaces_MachinePath* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<AvailableWorkspaces_MachinePath>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const AvailableWorkspaces_MachinePath& from);
  void MergeFrom(const AvailableWorkspaces_MachinePath& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(AvailableWorkspaces_MachinePath* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "AvailableWorkspaces.MachinePath";
  }
  protected:
  explicit AvailableWorkspaces_MachinePath(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_AvailableWorkspaces_2eproto);
    return ::descriptor_table_AvailableWorkspaces_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMachineIDFieldNumber = 1,
    kPathFieldNumber = 2,
  };
  // required string machineID = 1;
  bool has_machineid() const;
  private:
  bool _internal_has_machineid() const;
  public:
  void clear_machineid();
  const std::string& machineid() const;
  void set_machineid(const std::string& value);
  void set_machineid(std::string&& value);
  void set_machineid(const char* value);
  void set_machineid(const char* value, size_t size);
  std::string* mutable_machineid();
  std::string* release_machineid();
  void set_allocated_machineid(std::string* machineid);
  private:
  const std::string& _internal_machineid() const;
  void _internal_set_machineid(const std::string& value);
  std::string* _internal_mutable_machineid();
  public:

  // required string path = 2;
  bool has_path() const;
  private:
  bool _internal_has_path() const;
  public:
  void clear_path();
  const std::string& path() const;
  void set_path(const std::string& value);
  void set_path(std::string&& value);
  void set_path(const char* value);
  void set_path(const char* value, size_t size);
  std::string* mutable_path();
  std::string* release_path();
  void set_allocated_path(std::string* path);
  private:
  const std::string& _internal_path() const;
  void _internal_set_path(const std::string& value);
  std::string* _internal_mutable_path();
  public:

  // @@protoc_insertion_point(class_scope:AvailableWorkspaces.MachinePath)
 private:
  class _Internal;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr machineid_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr path_;
  friend struct ::TableStruct_AvailableWorkspaces_2eproto;
};
// -------------------------------------------------------------------

class AvailableWorkspaces PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:AvailableWorkspaces) */ {
 public:
  inline AvailableWorkspaces() : AvailableWorkspaces(nullptr) {}
  virtual ~AvailableWorkspaces();

  AvailableWorkspaces(const AvailableWorkspaces& from);
  AvailableWorkspaces(AvailableWorkspaces&& from) noexcept
    : AvailableWorkspaces() {
    *this = ::std::move(from);
  }

  inline AvailableWorkspaces& operator=(const AvailableWorkspaces& from) {
    CopyFrom(from);
    return *this;
  }
  inline AvailableWorkspaces& operator=(AvailableWorkspaces&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const AvailableWorkspaces& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const AvailableWorkspaces* internal_default_instance() {
    return reinterpret_cast<const AvailableWorkspaces*>(
               &_AvailableWorkspaces_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(AvailableWorkspaces& a, AvailableWorkspaces& b) {
    a.Swap(&b);
  }
  inline void Swap(AvailableWorkspaces* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(AvailableWorkspaces* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline AvailableWorkspaces* New() const final {
    return CreateMaybeMessage<AvailableWorkspaces>(nullptr);
  }

  AvailableWorkspaces* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<AvailableWorkspaces>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const AvailableWorkspaces& from);
  void MergeFrom(const AvailableWorkspaces& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(AvailableWorkspaces* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "AvailableWorkspaces";
  }
  protected:
  explicit AvailableWorkspaces(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_AvailableWorkspaces_2eproto);
    return ::descriptor_table_AvailableWorkspaces_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  typedef AvailableWorkspaces_MachinePath MachinePath;

  typedef AvailableWorkspaces_Status Status;
  static constexpr Status OK =
    AvailableWorkspaces_Status_OK;
  static constexpr Status FAIL =
    AvailableWorkspaces_Status_FAIL;
  static inline bool Status_IsValid(int value) {
    return AvailableWorkspaces_Status_IsValid(value);
  }
  static constexpr Status Status_MIN =
    AvailableWorkspaces_Status_Status_MIN;
  static constexpr Status Status_MAX =
    AvailableWorkspaces_Status_Status_MAX;
  static constexpr int Status_ARRAYSIZE =
    AvailableWorkspaces_Status_Status_ARRAYSIZE;
  static inline const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor*
  Status_descriptor() {
    return AvailableWorkspaces_Status_descriptor();
  }
  template<typename T>
  static inline const std::string& Status_Name(T enum_t_value) {
    static_assert(::std::is_same<T, Status>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function Status_Name.");
    return AvailableWorkspaces_Status_Name(enum_t_value);
  }
  static inline bool Status_Parse(::PROTOBUF_NAMESPACE_ID::ConstStringParam name,
      Status* value) {
    return AvailableWorkspaces_Status_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  enum : int {
    kPathsFieldNumber = 2,
    kStatusFieldNumber = 1,
  };
  // repeated .AvailableWorkspaces.MachinePath paths = 2;
  int paths_size() const;
  private:
  int _internal_paths_size() const;
  public:
  void clear_paths();
  ::AvailableWorkspaces_MachinePath* mutable_paths(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::AvailableWorkspaces_MachinePath >*
      mutable_paths();
  private:
  const ::AvailableWorkspaces_MachinePath& _internal_paths(int index) const;
  ::AvailableWorkspaces_MachinePath* _internal_add_paths();
  public:
  const ::AvailableWorkspaces_MachinePath& paths(int index) const;
  ::AvailableWorkspaces_MachinePath* add_paths();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::AvailableWorkspaces_MachinePath >&
      paths() const;

  // optional .AvailableWorkspaces.Status status = 1;
  bool has_status() const;
  private:
  bool _internal_has_status() const;
  public:
  void clear_status();
  ::AvailableWorkspaces_Status status() const;
  void set_status(::AvailableWorkspaces_Status value);
  private:
  ::AvailableWorkspaces_Status _internal_status() const;
  void _internal_set_status(::AvailableWorkspaces_Status value);
  public:

  // @@protoc_insertion_point(class_scope:AvailableWorkspaces)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::AvailableWorkspaces_MachinePath > paths_;
  int status_;
  friend struct ::TableStruct_AvailableWorkspaces_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// AvailableWorkspaces_MachinePath

// required string machineID = 1;
inline bool AvailableWorkspaces_MachinePath::_internal_has_machineid() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool AvailableWorkspaces_MachinePath::has_machineid() const {
  return _internal_has_machineid();
}
inline void AvailableWorkspaces_MachinePath::clear_machineid() {
  machineid_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& AvailableWorkspaces_MachinePath::machineid() const {
  // @@protoc_insertion_point(field_get:AvailableWorkspaces.MachinePath.machineID)
  return _internal_machineid();
}
inline void AvailableWorkspaces_MachinePath::set_machineid(const std::string& value) {
  _internal_set_machineid(value);
  // @@protoc_insertion_point(field_set:AvailableWorkspaces.MachinePath.machineID)
}
inline std::string* AvailableWorkspaces_MachinePath::mutable_machineid() {
  // @@protoc_insertion_point(field_mutable:AvailableWorkspaces.MachinePath.machineID)
  return _internal_mutable_machineid();
}
inline const std::string& AvailableWorkspaces_MachinePath::_internal_machineid() const {
  return machineid_.Get();
}
inline void AvailableWorkspaces_MachinePath::_internal_set_machineid(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  machineid_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value, GetArena());
}
inline void AvailableWorkspaces_MachinePath::set_machineid(std::string&& value) {
  _has_bits_[0] |= 0x00000001u;
  machineid_.Set(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:AvailableWorkspaces.MachinePath.machineID)
}
inline void AvailableWorkspaces_MachinePath::set_machineid(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000001u;
  machineid_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value),
              GetArena());
  // @@protoc_insertion_point(field_set_char:AvailableWorkspaces.MachinePath.machineID)
}
inline void AvailableWorkspaces_MachinePath::set_machineid(const char* value,
    size_t size) {
  _has_bits_[0] |= 0x00000001u;
  machineid_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:AvailableWorkspaces.MachinePath.machineID)
}
inline std::string* AvailableWorkspaces_MachinePath::_internal_mutable_machineid() {
  _has_bits_[0] |= 0x00000001u;
  return machineid_.Mutable(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline std::string* AvailableWorkspaces_MachinePath::release_machineid() {
  // @@protoc_insertion_point(field_release:AvailableWorkspaces.MachinePath.machineID)
  if (!_internal_has_machineid()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return machineid_.ReleaseNonDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void AvailableWorkspaces_MachinePath::set_allocated_machineid(std::string* machineid) {
  if (machineid != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  machineid_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), machineid,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:AvailableWorkspaces.MachinePath.machineID)
}

// required string path = 2;
inline bool AvailableWorkspaces_MachinePath::_internal_has_path() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool AvailableWorkspaces_MachinePath::has_path() const {
  return _internal_has_path();
}
inline void AvailableWorkspaces_MachinePath::clear_path() {
  path_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  _has_bits_[0] &= ~0x00000002u;
}
inline const std::string& AvailableWorkspaces_MachinePath::path() const {
  // @@protoc_insertion_point(field_get:AvailableWorkspaces.MachinePath.path)
  return _internal_path();
}
inline void AvailableWorkspaces_MachinePath::set_path(const std::string& value) {
  _internal_set_path(value);
  // @@protoc_insertion_point(field_set:AvailableWorkspaces.MachinePath.path)
}
inline std::string* AvailableWorkspaces_MachinePath::mutable_path() {
  // @@protoc_insertion_point(field_mutable:AvailableWorkspaces.MachinePath.path)
  return _internal_mutable_path();
}
inline const std::string& AvailableWorkspaces_MachinePath::_internal_path() const {
  return path_.Get();
}
inline void AvailableWorkspaces_MachinePath::_internal_set_path(const std::string& value) {
  _has_bits_[0] |= 0x00000002u;
  path_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value, GetArena());
}
inline void AvailableWorkspaces_MachinePath::set_path(std::string&& value) {
  _has_bits_[0] |= 0x00000002u;
  path_.Set(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:AvailableWorkspaces.MachinePath.path)
}
inline void AvailableWorkspaces_MachinePath::set_path(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000002u;
  path_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value),
              GetArena());
  // @@protoc_insertion_point(field_set_char:AvailableWorkspaces.MachinePath.path)
}
inline void AvailableWorkspaces_MachinePath::set_path(const char* value,
    size_t size) {
  _has_bits_[0] |= 0x00000002u;
  path_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:AvailableWorkspaces.MachinePath.path)
}
inline std::string* AvailableWorkspaces_MachinePath::_internal_mutable_path() {
  _has_bits_[0] |= 0x00000002u;
  return path_.Mutable(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline std::string* AvailableWorkspaces_MachinePath::release_path() {
  // @@protoc_insertion_point(field_release:AvailableWorkspaces.MachinePath.path)
  if (!_internal_has_path()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000002u;
  return path_.ReleaseNonDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void AvailableWorkspaces_MachinePath::set_allocated_path(std::string* path) {
  if (path != nullptr) {
    _has_bits_[0] |= 0x00000002u;
  } else {
    _has_bits_[0] &= ~0x00000002u;
  }
  path_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), path,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:AvailableWorkspaces.MachinePath.path)
}

// -------------------------------------------------------------------

// AvailableWorkspaces

// optional .AvailableWorkspaces.Status status = 1;
inline bool AvailableWorkspaces::_internal_has_status() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool AvailableWorkspaces::has_status() const {
  return _internal_has_status();
}
inline void AvailableWorkspaces::clear_status() {
  status_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::AvailableWorkspaces_Status AvailableWorkspaces::_internal_status() const {
  return static_cast< ::AvailableWorkspaces_Status >(status_);
}
inline ::AvailableWorkspaces_Status AvailableWorkspaces::status() const {
  // @@protoc_insertion_point(field_get:AvailableWorkspaces.status)
  return _internal_status();
}
inline void AvailableWorkspaces::_internal_set_status(::AvailableWorkspaces_Status value) {
  assert(::AvailableWorkspaces_Status_IsValid(value));
  _has_bits_[0] |= 0x00000001u;
  status_ = value;
}
inline void AvailableWorkspaces::set_status(::AvailableWorkspaces_Status value) {
  _internal_set_status(value);
  // @@protoc_insertion_point(field_set:AvailableWorkspaces.status)
}

// repeated .AvailableWorkspaces.MachinePath paths = 2;
inline int AvailableWorkspaces::_internal_paths_size() const {
  return paths_.size();
}
inline int AvailableWorkspaces::paths_size() const {
  return _internal_paths_size();
}
inline void AvailableWorkspaces::clear_paths() {
  paths_.Clear();
}
inline ::AvailableWorkspaces_MachinePath* AvailableWorkspaces::mutable_paths(int index) {
  // @@protoc_insertion_point(field_mutable:AvailableWorkspaces.paths)
  return paths_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::AvailableWorkspaces_MachinePath >*
AvailableWorkspaces::mutable_paths() {
  // @@protoc_insertion_point(field_mutable_list:AvailableWorkspaces.paths)
  return &paths_;
}
inline const ::AvailableWorkspaces_MachinePath& AvailableWorkspaces::_internal_paths(int index) const {
  return paths_.Get(index);
}
inline const ::AvailableWorkspaces_MachinePath& AvailableWorkspaces::paths(int index) const {
  // @@protoc_insertion_point(field_get:AvailableWorkspaces.paths)
  return _internal_paths(index);
}
inline ::AvailableWorkspaces_MachinePath* AvailableWorkspaces::_internal_add_paths() {
  return paths_.Add();
}
inline ::AvailableWorkspaces_MachinePath* AvailableWorkspaces::add_paths() {
  // @@protoc_insertion_point(field_add:AvailableWorkspaces.paths)
  return _internal_add_paths();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::AvailableWorkspaces_MachinePath >&
AvailableWorkspaces::paths() const {
  // @@protoc_insertion_point(field_list:AvailableWorkspaces.paths)
  return paths_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::AvailableWorkspaces_Status> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::AvailableWorkspaces_Status>() {
  return ::AvailableWorkspaces_Status_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_AvailableWorkspaces_2eproto
