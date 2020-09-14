// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: JobResponse.proto

#include "JobResponse.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)

class JobResponseDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<JobResponse>
      _instance;
} _JobResponse_default_instance_;
namespace protobuf_JobResponse_2eproto {
static void InitDefaultsJobResponse() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_JobResponse_default_instance_;
    new (ptr) ::JobResponse();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::JobResponse::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_JobResponse =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsJobResponse}, {}};

void InitDefaults() {
  ::google::protobuf::internal::InitSCC(&scc_info_JobResponse.base);
}

::google::protobuf::Metadata file_level_metadata[1];
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::JobResponse, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::JobResponse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::JobResponse, path_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::JobResponse, status_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::JobResponse, checksum_),
  0,
  2,
  1,
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 8, sizeof(::JobResponse)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::_JobResponse_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "JobResponse.proto", schemas, file_default_instances, TableStruct::offsets,
      file_level_metadata, file_level_enum_descriptors, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\021JobResponse.proto\"n\n\013JobResponse\022\014\n\004pa"
      "th\030\002 \002(\t\022#\n\006status\030\001 \002(\0162\023.JobResponse.S"
      "tatus\022\020\n\010checksum\030\003 \001(\t\"\032\n\006Status\022\006\n\002OK\020"
      "\000\022\010\n\004FAIL\020\001"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 131);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "JobResponse.proto", &protobuf_RegisterTypes);
}

void AddDescriptors() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_JobResponse_2eproto
const ::google::protobuf::EnumDescriptor* JobResponse_Status_descriptor() {
  protobuf_JobResponse_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_JobResponse_2eproto::file_level_enum_descriptors[0];
}
bool JobResponse_Status_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const JobResponse_Status JobResponse::OK;
const JobResponse_Status JobResponse::FAIL;
const JobResponse_Status JobResponse::Status_MIN;
const JobResponse_Status JobResponse::Status_MAX;
const int JobResponse::Status_ARRAYSIZE;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

// ===================================================================

void JobResponse::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int JobResponse::kPathFieldNumber;
const int JobResponse::kStatusFieldNumber;
const int JobResponse::kChecksumFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

JobResponse::JobResponse()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_JobResponse_2eproto::scc_info_JobResponse.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:JobResponse)
}
JobResponse::JobResponse(const JobResponse& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  path_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_path()) {
    path_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.path_);
  }
  checksum_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_checksum()) {
    checksum_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.checksum_);
  }
  status_ = from.status_;
  // @@protoc_insertion_point(copy_constructor:JobResponse)
}

void JobResponse::SharedCtor() {
  path_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  checksum_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  status_ = 0;
}

JobResponse::~JobResponse() {
  // @@protoc_insertion_point(destructor:JobResponse)
  SharedDtor();
}

void JobResponse::SharedDtor() {
  path_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  checksum_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void JobResponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* JobResponse::descriptor() {
  ::protobuf_JobResponse_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_JobResponse_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const JobResponse& JobResponse::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_JobResponse_2eproto::scc_info_JobResponse.base);
  return *internal_default_instance();
}


void JobResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:JobResponse)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 3u) {
    if (cached_has_bits & 0x00000001u) {
      path_.ClearNonDefaultToEmptyNoArena();
    }
    if (cached_has_bits & 0x00000002u) {
      checksum_.ClearNonDefaultToEmptyNoArena();
    }
  }
  status_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool JobResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:JobResponse)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .JobResponse.Status status = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::JobResponse_Status_IsValid(value)) {
            set_status(static_cast< ::JobResponse_Status >(value));
          } else {
            mutable_unknown_fields()->AddVarint(
                1, static_cast< ::google::protobuf::uint64>(value));
          }
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required string path = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_path()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->path().data(), static_cast<int>(this->path().length()),
            ::google::protobuf::internal::WireFormat::PARSE,
            "JobResponse.path");
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional string checksum = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(26u /* 26 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_checksum()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->checksum().data(), static_cast<int>(this->checksum().length()),
            ::google::protobuf::internal::WireFormat::PARSE,
            "JobResponse.checksum");
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:JobResponse)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:JobResponse)
  return false;
#undef DO_
}

void JobResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:JobResponse)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required .JobResponse.Status status = 1;
  if (cached_has_bits & 0x00000004u) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->status(), output);
  }

  // required string path = 2;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->path().data(), static_cast<int>(this->path().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "JobResponse.path");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->path(), output);
  }

  // optional string checksum = 3;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->checksum().data(), static_cast<int>(this->checksum().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "JobResponse.checksum");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->checksum(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:JobResponse)
}

::google::protobuf::uint8* JobResponse::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:JobResponse)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required .JobResponse.Status status = 1;
  if (cached_has_bits & 0x00000004u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->status(), target);
  }

  // required string path = 2;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->path().data(), static_cast<int>(this->path().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "JobResponse.path");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->path(), target);
  }

  // optional string checksum = 3;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->checksum().data(), static_cast<int>(this->checksum().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "JobResponse.checksum");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->checksum(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:JobResponse)
  return target;
}

size_t JobResponse::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:JobResponse)
  size_t total_size = 0;

  if (has_path()) {
    // required string path = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->path());
  }

  if (has_status()) {
    // required .JobResponse.Status status = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->status());
  }

  return total_size;
}
size_t JobResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:JobResponse)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000005) ^ 0x00000005) == 0) {  // All required fields are present.
    // required string path = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->path());

    // required .JobResponse.Status status = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->status());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  // optional string checksum = 3;
  if (has_checksum()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->checksum());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void JobResponse::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:JobResponse)
  GOOGLE_DCHECK_NE(&from, this);
  const JobResponse* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const JobResponse>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:JobResponse)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:JobResponse)
    MergeFrom(*source);
  }
}

void JobResponse::MergeFrom(const JobResponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:JobResponse)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 7u) {
    if (cached_has_bits & 0x00000001u) {
      set_has_path();
      path_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.path_);
    }
    if (cached_has_bits & 0x00000002u) {
      set_has_checksum();
      checksum_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.checksum_);
    }
    if (cached_has_bits & 0x00000004u) {
      status_ = from.status_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void JobResponse::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:JobResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void JobResponse::CopyFrom(const JobResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:JobResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool JobResponse::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000005) != 0x00000005) return false;
  return true;
}

void JobResponse::Swap(JobResponse* other) {
  if (other == this) return;
  InternalSwap(other);
}
void JobResponse::InternalSwap(JobResponse* other) {
  using std::swap;
  path_.Swap(&other->path_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  checksum_.Swap(&other->checksum_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(status_, other->status_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata JobResponse::GetMetadata() const {
  protobuf_JobResponse_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_JobResponse_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
namespace google {
namespace protobuf {
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::JobResponse* Arena::CreateMaybeMessage< ::JobResponse >(Arena* arena) {
  return Arena::CreateInternal< ::JobResponse >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
