// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DirectoryEntryList.proto

#include "DirectoryEntryList.pb.h"

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
extern PROTOBUF_INTERNAL_EXPORT_DirectoryEntryMessage_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_DirectoryEntryMessage_DirectoryEntryMessage_2eproto;
class DirectoryEntryListDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<DirectoryEntryList> _instance;
} _DirectoryEntryList_default_instance_;
static void InitDefaultsscc_info_DirectoryEntryList_DirectoryEntryList_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_DirectoryEntryList_default_instance_;
    new (ptr) ::DirectoryEntryList();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::DirectoryEntryList::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_DirectoryEntryList_DirectoryEntryList_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, 0, InitDefaultsscc_info_DirectoryEntryList_DirectoryEntryList_2eproto}, {
      &scc_info_DirectoryEntryMessage_DirectoryEntryMessage_2eproto.base,}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_DirectoryEntryList_2eproto[1];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_DirectoryEntryList_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_DirectoryEntryList_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_DirectoryEntryList_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::DirectoryEntryList, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::DirectoryEntryList, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::DirectoryEntryList, status_),
  PROTOBUF_FIELD_OFFSET(::DirectoryEntryList, list_),
  0,
  ~0u,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 7, sizeof(::DirectoryEntryList)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_DirectoryEntryList_default_instance_),
};

const char descriptor_table_protodef_DirectoryEntryList_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\030DirectoryEntryList.proto\032\033DirectoryEnt"
  "ryMessage.proto\"\204\001\n\022DirectoryEntryList\022*"
  "\n\006status\030\001 \002(\0162\032.DirectoryEntryList.Stat"
  "us\022$\n\004list\030\002 \003(\0132\026.DirectoryEntryMessage"
  "\"\034\n\006Status\022\006\n\002OK\020\000\022\n\n\006NOT_OK\020\001"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_DirectoryEntryList_2eproto_deps[1] = {
  &::descriptor_table_DirectoryEntryMessage_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_DirectoryEntryList_2eproto_sccs[1] = {
  &scc_info_DirectoryEntryList_DirectoryEntryList_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_DirectoryEntryList_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_DirectoryEntryList_2eproto = {
  false, false, descriptor_table_protodef_DirectoryEntryList_2eproto, "DirectoryEntryList.proto", 190,
  &descriptor_table_DirectoryEntryList_2eproto_once, descriptor_table_DirectoryEntryList_2eproto_sccs, descriptor_table_DirectoryEntryList_2eproto_deps, 1, 1,
  schemas, file_default_instances, TableStruct_DirectoryEntryList_2eproto::offsets,
  file_level_metadata_DirectoryEntryList_2eproto, 1, file_level_enum_descriptors_DirectoryEntryList_2eproto, file_level_service_descriptors_DirectoryEntryList_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_DirectoryEntryList_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_DirectoryEntryList_2eproto)), true);
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* DirectoryEntryList_Status_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_DirectoryEntryList_2eproto);
  return file_level_enum_descriptors_DirectoryEntryList_2eproto[0];
}
bool DirectoryEntryList_Status_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
constexpr DirectoryEntryList_Status DirectoryEntryList::OK;
constexpr DirectoryEntryList_Status DirectoryEntryList::NOT_OK;
constexpr DirectoryEntryList_Status DirectoryEntryList::Status_MIN;
constexpr DirectoryEntryList_Status DirectoryEntryList::Status_MAX;
constexpr int DirectoryEntryList::Status_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)

// ===================================================================

void DirectoryEntryList::InitAsDefaultInstance() {
}
class DirectoryEntryList::_Internal {
 public:
  using HasBits = decltype(std::declval<DirectoryEntryList>()._has_bits_);
  static void set_has_status(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static bool MissingRequiredFields(const HasBits& has_bits) {
    return ((has_bits[0] & 0x00000001) ^ 0x00000001) != 0;
  }
};

void DirectoryEntryList::clear_list() {
  list_.Clear();
}
DirectoryEntryList::DirectoryEntryList(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena),
  list_(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:DirectoryEntryList)
}
DirectoryEntryList::DirectoryEntryList(const DirectoryEntryList& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_),
      list_(from.list_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  status_ = from.status_;
  // @@protoc_insertion_point(copy_constructor:DirectoryEntryList)
}

void DirectoryEntryList::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_DirectoryEntryList_DirectoryEntryList_2eproto.base);
  status_ = 0;
}

DirectoryEntryList::~DirectoryEntryList() {
  // @@protoc_insertion_point(destructor:DirectoryEntryList)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void DirectoryEntryList::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
}

void DirectoryEntryList::ArenaDtor(void* object) {
  DirectoryEntryList* _this = reinterpret_cast< DirectoryEntryList* >(object);
  (void)_this;
}
void DirectoryEntryList::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void DirectoryEntryList::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const DirectoryEntryList& DirectoryEntryList::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_DirectoryEntryList_DirectoryEntryList_2eproto.base);
  return *internal_default_instance();
}


void DirectoryEntryList::Clear() {
// @@protoc_insertion_point(message_clear_start:DirectoryEntryList)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  list_.Clear();
  status_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* DirectoryEntryList::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // required .DirectoryEntryList.Status status = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          if (PROTOBUF_PREDICT_TRUE(::DirectoryEntryList_Status_IsValid(val))) {
            _internal_set_status(static_cast<::DirectoryEntryList_Status>(val));
          } else {
            ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(1, val, mutable_unknown_fields());
          }
        } else goto handle_unusual;
        continue;
      // repeated .DirectoryEntryMessage list = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_list(), ptr);
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

::PROTOBUF_NAMESPACE_ID::uint8* DirectoryEntryList::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:DirectoryEntryList)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required .DirectoryEntryList.Status status = 1;
  if (cached_has_bits & 0x00000001u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_status(), target);
  }

  // repeated .DirectoryEntryMessage list = 2;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_list_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(2, this->_internal_list(i), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:DirectoryEntryList)
  return target;
}

size_t DirectoryEntryList::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:DirectoryEntryList)
  size_t total_size = 0;

  // required .DirectoryEntryList.Status status = 1;
  if (_internal_has_status()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_status());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .DirectoryEntryMessage list = 2;
  total_size += 1UL * this->_internal_list_size();
  for (const auto& msg : this->list_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void DirectoryEntryList::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:DirectoryEntryList)
  GOOGLE_DCHECK_NE(&from, this);
  const DirectoryEntryList* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<DirectoryEntryList>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:DirectoryEntryList)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:DirectoryEntryList)
    MergeFrom(*source);
  }
}

void DirectoryEntryList::MergeFrom(const DirectoryEntryList& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:DirectoryEntryList)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  list_.MergeFrom(from.list_);
  if (from._internal_has_status()) {
    _internal_set_status(from._internal_status());
  }
}

void DirectoryEntryList::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:DirectoryEntryList)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void DirectoryEntryList::CopyFrom(const DirectoryEntryList& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:DirectoryEntryList)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DirectoryEntryList::IsInitialized() const {
  if (_Internal::MissingRequiredFields(_has_bits_)) return false;
  if (!::PROTOBUF_NAMESPACE_ID::internal::AllAreInitialized(list_)) return false;
  return true;
}

void DirectoryEntryList::InternalSwap(DirectoryEntryList* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  list_.InternalSwap(&other->list_);
  swap(status_, other->status_);
}

::PROTOBUF_NAMESPACE_ID::Metadata DirectoryEntryList::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::DirectoryEntryList* Arena::CreateMaybeMessage< ::DirectoryEntryList >(Arena* arena) {
  return Arena::CreateMessageInternal< ::DirectoryEntryList >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
