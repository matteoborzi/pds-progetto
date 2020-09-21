// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Workspace.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Workspace_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Workspace_2eproto

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
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Workspace_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Workspace_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Workspace_2eproto;
class Workspace;
class WorkspaceDefaultTypeInternal;
extern WorkspaceDefaultTypeInternal _Workspace_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::Workspace* Arena::CreateMaybeMessage<::Workspace>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class Workspace PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Workspace) */ {
 public:
  inline Workspace() : Workspace(nullptr) {}
  virtual ~Workspace();

  Workspace(const Workspace& from);
  Workspace(Workspace&& from) noexcept
    : Workspace() {
    *this = ::std::move(from);
  }

  inline Workspace& operator=(const Workspace& from) {
    CopyFrom(from);
    return *this;
  }
  inline Workspace& operator=(Workspace&& from) noexcept {
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
  static const Workspace& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Workspace* internal_default_instance() {
    return reinterpret_cast<const Workspace*>(
               &_Workspace_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Workspace& a, Workspace& b) {
    a.Swap(&b);
  }
  inline void Swap(Workspace* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Workspace* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Workspace* New() const final {
    return CreateMaybeMessage<Workspace>(nullptr);
  }

  Workspace* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Workspace>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Workspace& from);
  void MergeFrom(const Workspace& from);
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
  void InternalSwap(Workspace* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Workspace";
  }
  protected:
  explicit Workspace(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_Workspace_2eproto);
    return ::descriptor_table_Workspace_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kPathFieldNumber = 1,
    kMachineIDFieldNumber = 2,
    kRestoreFieldNumber = 3,
  };
  // required string path = 1;
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

  // required string machineID = 2;
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

  // required bool restore = 3;
  bool has_restore() const;
  private:
  bool _internal_has_restore() const;
  public:
  void clear_restore();
  bool restore() const;
  void set_restore(bool value);
  private:
  bool _internal_restore() const;
  void _internal_set_restore(bool value);
  public:

  // @@protoc_insertion_point(class_scope:Workspace)
 private:
  class _Internal;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr path_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr machineid_;
  bool restore_;
  friend struct ::TableStruct_Workspace_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Workspace

// required string path = 1;
inline bool Workspace::_internal_has_path() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool Workspace::has_path() const {
  return _internal_has_path();
}
inline void Workspace::clear_path() {
  path_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& Workspace::path() const {
  // @@protoc_insertion_point(field_get:Workspace.path)
  return _internal_path();
}
inline void Workspace::set_path(const std::string& value) {
  _internal_set_path(value);
  // @@protoc_insertion_point(field_set:Workspace.path)
}
inline std::string* Workspace::mutable_path() {
  // @@protoc_insertion_point(field_mutable:Workspace.path)
  return _internal_mutable_path();
}
inline const std::string& Workspace::_internal_path() const {
  return path_.Get();
}
inline void Workspace::_internal_set_path(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  path_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value, GetArena());
}
inline void Workspace::set_path(std::string&& value) {
  _has_bits_[0] |= 0x00000001u;
  path_.Set(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:Workspace.path)
}
inline void Workspace::set_path(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000001u;
  path_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value),
              GetArena());
  // @@protoc_insertion_point(field_set_char:Workspace.path)
}
inline void Workspace::set_path(const char* value,
    size_t size) {
  _has_bits_[0] |= 0x00000001u;
  path_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:Workspace.path)
}
inline std::string* Workspace::_internal_mutable_path() {
  _has_bits_[0] |= 0x00000001u;
  return path_.Mutable(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline std::string* Workspace::release_path() {
  // @@protoc_insertion_point(field_release:Workspace.path)
  if (!_internal_has_path()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return path_.ReleaseNonDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void Workspace::set_allocated_path(std::string* path) {
  if (path != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  path_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), path,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:Workspace.path)
}

// required string machineID = 2;
inline bool Workspace::_internal_has_machineid() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool Workspace::has_machineid() const {
  return _internal_has_machineid();
}
inline void Workspace::clear_machineid() {
  machineid_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  _has_bits_[0] &= ~0x00000002u;
}
inline const std::string& Workspace::machineid() const {
  // @@protoc_insertion_point(field_get:Workspace.machineID)
  return _internal_machineid();
}
inline void Workspace::set_machineid(const std::string& value) {
  _internal_set_machineid(value);
  // @@protoc_insertion_point(field_set:Workspace.machineID)
}
inline std::string* Workspace::mutable_machineid() {
  // @@protoc_insertion_point(field_mutable:Workspace.machineID)
  return _internal_mutable_machineid();
}
inline const std::string& Workspace::_internal_machineid() const {
  return machineid_.Get();
}
inline void Workspace::_internal_set_machineid(const std::string& value) {
  _has_bits_[0] |= 0x00000002u;
  machineid_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value, GetArena());
}
inline void Workspace::set_machineid(std::string&& value) {
  _has_bits_[0] |= 0x00000002u;
  machineid_.Set(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:Workspace.machineID)
}
inline void Workspace::set_machineid(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000002u;
  machineid_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value),
              GetArena());
  // @@protoc_insertion_point(field_set_char:Workspace.machineID)
}
inline void Workspace::set_machineid(const char* value,
    size_t size) {
  _has_bits_[0] |= 0x00000002u;
  machineid_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:Workspace.machineID)
}
inline std::string* Workspace::_internal_mutable_machineid() {
  _has_bits_[0] |= 0x00000002u;
  return machineid_.Mutable(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline std::string* Workspace::release_machineid() {
  // @@protoc_insertion_point(field_release:Workspace.machineID)
  if (!_internal_has_machineid()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000002u;
  return machineid_.ReleaseNonDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void Workspace::set_allocated_machineid(std::string* machineid) {
  if (machineid != nullptr) {
    _has_bits_[0] |= 0x00000002u;
  } else {
    _has_bits_[0] &= ~0x00000002u;
  }
  machineid_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), machineid,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:Workspace.machineID)
}

// required bool restore = 3;
inline bool Workspace::_internal_has_restore() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool Workspace::has_restore() const {
  return _internal_has_restore();
}
inline void Workspace::clear_restore() {
  restore_ = false;
  _has_bits_[0] &= ~0x00000004u;
}
inline bool Workspace::_internal_restore() const {
  return restore_;
}
inline bool Workspace::restore() const {
  // @@protoc_insertion_point(field_get:Workspace.restore)
  return _internal_restore();
}
inline void Workspace::_internal_set_restore(bool value) {
  _has_bits_[0] |= 0x00000004u;
  restore_ = value;
}
inline void Workspace::set_restore(bool value) {
  _internal_set_restore(value);
  // @@protoc_insertion_point(field_set:Workspace.restore)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Workspace_2eproto
