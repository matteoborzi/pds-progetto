// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AvailableWorkspaces.proto

#include "AvailableWorkspaces.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
extern PROTOBUF_INTERNAL_EXPORT_AvailableWorkspaces_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_AvailableWorkspaces_MachinePath_AvailableWorkspaces_2eproto;
class AvailableWorkspaces_MachinePathDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<AvailableWorkspaces_MachinePath> _instance;
} _AvailableWorkspaces_MachinePath_default_instance_;
class AvailableWorkspacesDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<AvailableWorkspaces> _instance;
} _AvailableWorkspaces_default_instance_;
static void InitDefaultsscc_info_AvailableWorkspaces_AvailableWorkspaces_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_AvailableWorkspaces_default_instance_;
    new (ptr) ::AvailableWorkspaces();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::AvailableWorkspaces::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_AvailableWorkspaces_AvailableWorkspaces_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, 0, InitDefaultsscc_info_AvailableWorkspaces_AvailableWorkspaces_2eproto}, {
      &scc_info_AvailableWorkspaces_MachinePath_AvailableWorkspaces_2eproto.base,}};

static void InitDefaultsscc_info_AvailableWorkspaces_MachinePath_AvailableWorkspaces_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_AvailableWorkspaces_MachinePath_default_instance_;
    new (ptr) ::AvailableWorkspaces_MachinePath();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::AvailableWorkspaces_MachinePath::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_AvailableWorkspaces_MachinePath_AvailableWorkspaces_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_AvailableWorkspaces_MachinePath_AvailableWorkspaces_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_AvailableWorkspaces_2eproto[2];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_AvailableWorkspaces_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_AvailableWorkspaces_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_AvailableWorkspaces_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::AvailableWorkspaces_MachinePath, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::AvailableWorkspaces_MachinePath, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::AvailableWorkspaces_MachinePath, machineid_),
  PROTOBUF_FIELD_OFFSET(::AvailableWorkspaces_MachinePath, path_),
  0,
  1,
  PROTOBUF_FIELD_OFFSET(::AvailableWorkspaces, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::AvailableWorkspaces, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::AvailableWorkspaces, status_),
  PROTOBUF_FIELD_OFFSET(::AvailableWorkspaces, paths_),
  0,
  ~0u,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 7, sizeof(::AvailableWorkspaces_MachinePath)},
  { 9, 16, sizeof(::AvailableWorkspaces)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_AvailableWorkspaces_MachinePath_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_AvailableWorkspaces_default_instance_),
};

const char descriptor_table_protodef_AvailableWorkspaces_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\031AvailableWorkspaces.proto\"\277\001\n\023Availabl"
  "eWorkspaces\022+\n\006status\030\001 \001(\0162\033.AvailableW"
  "orkspaces.Status\022/\n\005paths\030\002 \003(\0132 .Availa"
  "bleWorkspaces.MachinePath\032.\n\013MachinePath"
  "\022\021\n\tmachineID\030\001 \002(\t\022\014\n\004path\030\002 \002(\t\"\032\n\006Sta"
  "tus\022\006\n\002OK\020\000\022\010\n\004FAIL\020\001"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_AvailableWorkspaces_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_AvailableWorkspaces_2eproto_sccs[2] = {
  &scc_info_AvailableWorkspaces_AvailableWorkspaces_2eproto.base,
  &scc_info_AvailableWorkspaces_MachinePath_AvailableWorkspaces_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_AvailableWorkspaces_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_AvailableWorkspaces_2eproto = {
  false, false, descriptor_table_protodef_AvailableWorkspaces_2eproto, "AvailableWorkspaces.proto", 221,
  &descriptor_table_AvailableWorkspaces_2eproto_once, descriptor_table_AvailableWorkspaces_2eproto_sccs, descriptor_table_AvailableWorkspaces_2eproto_deps, 2, 0,
  schemas, file_default_instances, TableStruct_AvailableWorkspaces_2eproto::offsets,
  file_level_metadata_AvailableWorkspaces_2eproto, 2, file_level_enum_descriptors_AvailableWorkspaces_2eproto, file_level_service_descriptors_AvailableWorkspaces_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_AvailableWorkspaces_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_AvailableWorkspaces_2eproto)), true);
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* AvailableWorkspaces_Status_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_AvailableWorkspaces_2eproto);
  return file_level_enum_descriptors_AvailableWorkspaces_2eproto[0];
}
bool AvailableWorkspaces_Status_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
constexpr AvailableWorkspaces_Status AvailableWorkspaces::OK;
constexpr AvailableWorkspaces_Status AvailableWorkspaces::FAIL;
constexpr AvailableWorkspaces_Status AvailableWorkspaces::Status_MIN;
constexpr AvailableWorkspaces_Status AvailableWorkspaces::Status_MAX;
constexpr int AvailableWorkspaces::Status_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)

// ===================================================================

void AvailableWorkspaces_MachinePath::InitAsDefaultInstance() {
}
class AvailableWorkspaces_MachinePath::_Internal {
 public:
  using HasBits = decltype(std::declval<AvailableWorkspaces_MachinePath>()._has_bits_);
  static void set_has_machineid(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_path(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static bool MissingRequiredFields(const HasBits& has_bits) {
    return ((has_bits[0] & 0x00000003) ^ 0x00000003) != 0;
  }
};

AvailableWorkspaces_MachinePath::AvailableWorkspaces_MachinePath(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:AvailableWorkspaces.MachinePath)
}
AvailableWorkspaces_MachinePath::AvailableWorkspaces_MachinePath(const AvailableWorkspaces_MachinePath& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  machineid_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from._internal_has_machineid()) {
    machineid_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_machineid(),
      GetArena());
  }
  path_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from._internal_has_path()) {
    path_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_path(),
      GetArena());
  }
  // @@protoc_insertion_point(copy_constructor:AvailableWorkspaces.MachinePath)
}

void AvailableWorkspaces_MachinePath::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_AvailableWorkspaces_MachinePath_AvailableWorkspaces_2eproto.base);
  machineid_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  path_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

AvailableWorkspaces_MachinePath::~AvailableWorkspaces_MachinePath() {
  // @@protoc_insertion_point(destructor:AvailableWorkspaces.MachinePath)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void AvailableWorkspaces_MachinePath::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  machineid_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  path_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void AvailableWorkspaces_MachinePath::ArenaDtor(void* object) {
  AvailableWorkspaces_MachinePath* _this = reinterpret_cast< AvailableWorkspaces_MachinePath* >(object);
  (void)_this;
}
void AvailableWorkspaces_MachinePath::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void AvailableWorkspaces_MachinePath::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const AvailableWorkspaces_MachinePath& AvailableWorkspaces_MachinePath::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_AvailableWorkspaces_MachinePath_AvailableWorkspaces_2eproto.base);
  return *internal_default_instance();
}


void AvailableWorkspaces_MachinePath::Clear() {
// @@protoc_insertion_point(message_clear_start:AvailableWorkspaces.MachinePath)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      machineid_.ClearNonDefaultToEmpty();
    }
    if (cached_has_bits & 0x00000002u) {
      path_.ClearNonDefaultToEmpty();
    }
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* AvailableWorkspaces_MachinePath::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // required string machineID = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_machineid();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          #ifndef NDEBUG
          ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "AvailableWorkspaces.MachinePath.machineID");
          #endif  // !NDEBUG
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // required string path = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_path();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          #ifndef NDEBUG
          ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "AvailableWorkspaces.MachinePath.path");
          #endif  // !NDEBUG
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* AvailableWorkspaces_MachinePath::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:AvailableWorkspaces.MachinePath)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required string machineID = 1;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_machineid().data(), static_cast<int>(this->_internal_machineid().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "AvailableWorkspaces.MachinePath.machineID");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_machineid(), target);
  }

  // required string path = 2;
  if (cached_has_bits & 0x00000002u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_path().data(), static_cast<int>(this->_internal_path().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "AvailableWorkspaces.MachinePath.path");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_path(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:AvailableWorkspaces.MachinePath)
  return target;
}

size_t AvailableWorkspaces_MachinePath::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:AvailableWorkspaces.MachinePath)
  size_t total_size = 0;

  if (_internal_has_machineid()) {
    // required string machineID = 1;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_machineid());
  }

  if (_internal_has_path()) {
    // required string path = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_path());
  }

  return total_size;
}
size_t AvailableWorkspaces_MachinePath::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:AvailableWorkspaces.MachinePath)
  size_t total_size = 0;

  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required string machineID = 1;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_machineid());

    // required string path = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_path());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void AvailableWorkspaces_MachinePath::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:AvailableWorkspaces.MachinePath)
  GOOGLE_DCHECK_NE(&from, this);
  const AvailableWorkspaces_MachinePath* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<AvailableWorkspaces_MachinePath>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:AvailableWorkspaces.MachinePath)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:AvailableWorkspaces.MachinePath)
    MergeFrom(*source);
  }
}

void AvailableWorkspaces_MachinePath::MergeFrom(const AvailableWorkspaces_MachinePath& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:AvailableWorkspaces.MachinePath)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      _internal_set_machineid(from._internal_machineid());
    }
    if (cached_has_bits & 0x00000002u) {
      _internal_set_path(from._internal_path());
    }
  }
}

void AvailableWorkspaces_MachinePath::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:AvailableWorkspaces.MachinePath)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AvailableWorkspaces_MachinePath::CopyFrom(const AvailableWorkspaces_MachinePath& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:AvailableWorkspaces.MachinePath)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AvailableWorkspaces_MachinePath::IsInitialized() const {
  if (_Internal::MissingRequiredFields(_has_bits_)) return false;
  return true;
}

void AvailableWorkspaces_MachinePath::InternalSwap(AvailableWorkspaces_MachinePath* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  machineid_.Swap(&other->machineid_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  path_.Swap(&other->path_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}

::PROTOBUF_NAMESPACE_ID::Metadata AvailableWorkspaces_MachinePath::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void AvailableWorkspaces::InitAsDefaultInstance() {
}
class AvailableWorkspaces::_Internal {
 public:
  using HasBits = decltype(std::declval<AvailableWorkspaces>()._has_bits_);
  static void set_has_status(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

AvailableWorkspaces::AvailableWorkspaces(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena),
  paths_(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:AvailableWorkspaces)
}
AvailableWorkspaces::AvailableWorkspaces(const AvailableWorkspaces& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_),
      paths_(from.paths_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  status_ = from.status_;
  // @@protoc_insertion_point(copy_constructor:AvailableWorkspaces)
}

void AvailableWorkspaces::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_AvailableWorkspaces_AvailableWorkspaces_2eproto.base);
  status_ = 0;
}

AvailableWorkspaces::~AvailableWorkspaces() {
  // @@protoc_insertion_point(destructor:AvailableWorkspaces)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void AvailableWorkspaces::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
}

void AvailableWorkspaces::ArenaDtor(void* object) {
  AvailableWorkspaces* _this = reinterpret_cast< AvailableWorkspaces* >(object);
  (void)_this;
}
void AvailableWorkspaces::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void AvailableWorkspaces::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const AvailableWorkspaces& AvailableWorkspaces::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_AvailableWorkspaces_AvailableWorkspaces_2eproto.base);
  return *internal_default_instance();
}


void AvailableWorkspaces::Clear() {
// @@protoc_insertion_point(message_clear_start:AvailableWorkspaces)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  paths_.Clear();
  status_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* AvailableWorkspaces::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional .AvailableWorkspaces.Status status = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          if (PROTOBUF_PREDICT_TRUE(::AvailableWorkspaces_Status_IsValid(val))) {
            _internal_set_status(static_cast<::AvailableWorkspaces_Status>(val));
          } else {
            ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(1, val, mutable_unknown_fields());
          }
        } else goto handle_unusual;
        continue;
      // repeated .AvailableWorkspaces.MachinePath paths = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_paths(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<18>(ptr));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* AvailableWorkspaces::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:AvailableWorkspaces)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional .AvailableWorkspaces.Status status = 1;
  if (cached_has_bits & 0x00000001u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_status(), target);
  }

  // repeated .AvailableWorkspaces.MachinePath paths = 2;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_paths_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(2, this->_internal_paths(i), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:AvailableWorkspaces)
  return target;
}

size_t AvailableWorkspaces::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:AvailableWorkspaces)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .AvailableWorkspaces.MachinePath paths = 2;
  total_size += 1UL * this->_internal_paths_size();
  for (const auto& msg : this->paths_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // optional .AvailableWorkspaces.Status status = 1;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_status());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void AvailableWorkspaces::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:AvailableWorkspaces)
  GOOGLE_DCHECK_NE(&from, this);
  const AvailableWorkspaces* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<AvailableWorkspaces>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:AvailableWorkspaces)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:AvailableWorkspaces)
    MergeFrom(*source);
  }
}

void AvailableWorkspaces::MergeFrom(const AvailableWorkspaces& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:AvailableWorkspaces)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  paths_.MergeFrom(from.paths_);
  if (from._internal_has_status()) {
    _internal_set_status(from._internal_status());
  }
}

void AvailableWorkspaces::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:AvailableWorkspaces)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AvailableWorkspaces::CopyFrom(const AvailableWorkspaces& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:AvailableWorkspaces)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AvailableWorkspaces::IsInitialized() const {
  if (!::PROTOBUF_NAMESPACE_ID::internal::AllAreInitialized(paths_)) return false;
  return true;
}

void AvailableWorkspaces::InternalSwap(AvailableWorkspaces* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  paths_.InternalSwap(&other->paths_);
  swap(status_, other->status_);
}

::PROTOBUF_NAMESPACE_ID::Metadata AvailableWorkspaces::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::AvailableWorkspaces_MachinePath* Arena::CreateMaybeMessage< ::AvailableWorkspaces_MachinePath >(Arena* arena) {
  return Arena::CreateMessageInternal< ::AvailableWorkspaces_MachinePath >(arena);
}
template<> PROTOBUF_NOINLINE ::AvailableWorkspaces* Arena::CreateMaybeMessage< ::AvailableWorkspaces >(Arena* arena) {
  return Arena::CreateMessageInternal< ::AvailableWorkspaces >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
