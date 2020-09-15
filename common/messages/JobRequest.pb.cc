// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: JobRequest.proto

#include "JobRequest.pb.h"

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
class JobRequestDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<JobRequest> _instance;
} _JobRequest_default_instance_;
static void InitDefaultsscc_info_JobRequest_JobRequest_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_JobRequest_default_instance_;
    new (ptr) ::JobRequest();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::JobRequest::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_JobRequest_JobRequest_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_JobRequest_JobRequest_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_JobRequest_2eproto[1];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_JobRequest_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_JobRequest_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_JobRequest_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::JobRequest, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::JobRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::JobRequest, pbaction_),
  PROTOBUF_FIELD_OFFSET(::JobRequest, path_),
  PROTOBUF_FIELD_OFFSET(::JobRequest, size_),
  2,
  0,
  1,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 8, sizeof(::JobRequest)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_JobRequest_default_instance_),
};

const char descriptor_table_protodef_JobRequest_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\020JobRequest.proto\"\244\001\n\nJobRequest\022&\n\010pba"
  "ction\030\001 \002(\0162\024.JobRequest.PBAction\022\014\n\004pat"
  "h\030\002 \002(\t\022\014\n\004size\030\003 \001(\004\"R\n\010PBAction\022\014\n\010ADD"
  "_FILE\020\000\022\021\n\rADD_DIRECTORY\020\001\022\n\n\006UPDATE\020\002\022\n"
  "\n\006DELETE\020\003\022\r\n\tCANCELLED\020\004"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_JobRequest_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_JobRequest_2eproto_sccs[1] = {
  &scc_info_JobRequest_JobRequest_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_JobRequest_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_JobRequest_2eproto = {
  false, false, descriptor_table_protodef_JobRequest_2eproto, "JobRequest.proto", 185,
  &descriptor_table_JobRequest_2eproto_once, descriptor_table_JobRequest_2eproto_sccs, descriptor_table_JobRequest_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_JobRequest_2eproto::offsets,
  file_level_metadata_JobRequest_2eproto, 1, file_level_enum_descriptors_JobRequest_2eproto, file_level_service_descriptors_JobRequest_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_JobRequest_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_JobRequest_2eproto)), true);
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* JobRequest_PBAction_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_JobRequest_2eproto);
  return file_level_enum_descriptors_JobRequest_2eproto[0];
}
bool JobRequest_PBAction_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      return true;
    default:
      return false;
  }
}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
constexpr JobRequest_PBAction JobRequest::ADD_FILE;
constexpr JobRequest_PBAction JobRequest::ADD_DIRECTORY;
constexpr JobRequest_PBAction JobRequest::UPDATE;
constexpr JobRequest_PBAction JobRequest::DELETE;
constexpr JobRequest_PBAction JobRequest::CANCELLED;
constexpr JobRequest_PBAction JobRequest::PBAction_MIN;
constexpr JobRequest_PBAction JobRequest::PBAction_MAX;
constexpr int JobRequest::PBAction_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)

// ===================================================================

void JobRequest::InitAsDefaultInstance() {
}
class JobRequest::_Internal {
 public:
  using HasBits = decltype(std::declval<JobRequest>()._has_bits_);
  static void set_has_pbaction(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_path(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_size(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static bool MissingRequiredFields(const HasBits& has_bits) {
    return ((has_bits[0] & 0x00000005) ^ 0x00000005) != 0;
  }
};

JobRequest::JobRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:JobRequest)
}
JobRequest::JobRequest(const JobRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  path_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from._internal_has_path()) {
    path_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_path(),
      GetArena());
  }
  ::memcpy(&size_, &from.size_,
    static_cast<size_t>(reinterpret_cast<char*>(&pbaction_) -
    reinterpret_cast<char*>(&size_)) + sizeof(pbaction_));
  // @@protoc_insertion_point(copy_constructor:JobRequest)
}

void JobRequest::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_JobRequest_JobRequest_2eproto.base);
  path_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  ::memset(&size_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&pbaction_) -
      reinterpret_cast<char*>(&size_)) + sizeof(pbaction_));
}

JobRequest::~JobRequest() {
  // @@protoc_insertion_point(destructor:JobRequest)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void JobRequest::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  path_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void JobRequest::ArenaDtor(void* object) {
  JobRequest* _this = reinterpret_cast< JobRequest* >(object);
  (void)_this;
}
void JobRequest::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void JobRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const JobRequest& JobRequest::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_JobRequest_JobRequest_2eproto.base);
  return *internal_default_instance();
}


void JobRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:JobRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    path_.ClearNonDefaultToEmpty();
  }
  if (cached_has_bits & 0x00000006u) {
    ::memset(&size_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&pbaction_) -
        reinterpret_cast<char*>(&size_)) + sizeof(pbaction_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* JobRequest::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // required .JobRequest.PBAction pbaction = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          if (PROTOBUF_PREDICT_TRUE(::JobRequest_PBAction_IsValid(val))) {
            _internal_set_pbaction(static_cast<::JobRequest_PBAction>(val));
          } else {
            ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(1, val, mutable_unknown_fields());
          }
        } else goto handle_unusual;
        continue;
      // required string path = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_path();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          #ifndef NDEBUG
          ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "JobRequest.path");
          #endif  // !NDEBUG
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional uint64 size = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          _Internal::set_has_size(&has_bits);
          size_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
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

::PROTOBUF_NAMESPACE_ID::uint8* JobRequest::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:JobRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required .JobRequest.PBAction pbaction = 1;
  if (cached_has_bits & 0x00000004u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_pbaction(), target);
  }

  // required string path = 2;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_path().data(), static_cast<int>(this->_internal_path().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "JobRequest.path");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_path(), target);
  }

  // optional uint64 size = 3;
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(3, this->_internal_size(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:JobRequest)
  return target;
}

size_t JobRequest::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:JobRequest)
  size_t total_size = 0;

  if (_internal_has_path()) {
    // required string path = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_path());
  }

  if (_internal_has_pbaction()) {
    // required .JobRequest.PBAction pbaction = 1;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_pbaction());
  }

  return total_size;
}
size_t JobRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:JobRequest)
  size_t total_size = 0;

  if (((_has_bits_[0] & 0x00000005) ^ 0x00000005) == 0) {  // All required fields are present.
    // required string path = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_path());

    // required .JobRequest.PBAction pbaction = 1;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_pbaction());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // optional uint64 size = 3;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000002u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
        this->_internal_size());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void JobRequest::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:JobRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const JobRequest* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<JobRequest>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:JobRequest)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:JobRequest)
    MergeFrom(*source);
  }
}

void JobRequest::MergeFrom(const JobRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:JobRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000007u) {
    if (cached_has_bits & 0x00000001u) {
      _internal_set_path(from._internal_path());
    }
    if (cached_has_bits & 0x00000002u) {
      size_ = from.size_;
    }
    if (cached_has_bits & 0x00000004u) {
      pbaction_ = from.pbaction_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void JobRequest::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:JobRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void JobRequest::CopyFrom(const JobRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:JobRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool JobRequest::IsInitialized() const {
  if (_Internal::MissingRequiredFields(_has_bits_)) return false;
  return true;
}

void JobRequest::InternalSwap(JobRequest* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  path_.Swap(&other->path_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(JobRequest, pbaction_)
      + sizeof(JobRequest::pbaction_)
      - PROTOBUF_FIELD_OFFSET(JobRequest, size_)>(
          reinterpret_cast<char*>(&size_),
          reinterpret_cast<char*>(&other->size_));
}

::PROTOBUF_NAMESPACE_ID::Metadata JobRequest::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::JobRequest* Arena::CreateMaybeMessage< ::JobRequest >(Arena* arena) {
  return Arena::CreateMessageInternal< ::JobRequest >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>