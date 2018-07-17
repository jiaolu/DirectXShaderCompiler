///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// DxilConstants.h                                                           //
// Copyright (C) Microsoft Corporation. All rights reserved.                 //
// This file is distributed under the University of Illinois Open Source     //
// License. See LICENSE.TXT for details.                                     //
//                                                                           //
// Essential DXIL constants.                                                 //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <stdint.h>

namespace hlsl {

/* <py>
import hctdb_instrhelp
</py> */

// TODO:
//   2. get rid of DXIL namespace.
//   3. use class enum for shader flags.
//   4. use class enum for address spaces.

namespace DXIL {
  // DXIL version.
  const unsigned kDxilMajor = 1;
  const unsigned kDxilMinor = 3;

  inline unsigned MakeDxilVersion(unsigned DxilMajor, unsigned DxilMinor) {
    return 0 | (DxilMajor << 8) | (DxilMinor);
  }
  inline unsigned GetCurrentDxilVersion() { return MakeDxilVersion(kDxilMajor, kDxilMinor); }
  inline unsigned GetDxilVersionMajor(unsigned DxilVersion) { return (DxilVersion >> 8) & 0xFF; }
  inline unsigned GetDxilVersionMinor(unsigned DxilVersion) { return DxilVersion & 0xFF; }

  // Shader flags.
  const unsigned kDisableOptimizations          = 0x00000001; // D3D11_1_SB_GLOBAL_FLAG_SKIP_OPTIMIZATION
  const unsigned kDisableMathRefactoring        = 0x00000002; //~D3D10_SB_GLOBAL_FLAG_REFACTORING_ALLOWED
  const unsigned kEnableDoublePrecision         = 0x00000004; // D3D11_SB_GLOBAL_FLAG_ENABLE_DOUBLE_PRECISION_FLOAT_OPS
  const unsigned kForceEarlyDepthStencil        = 0x00000008; // D3D11_SB_GLOBAL_FLAG_FORCE_EARLY_DEPTH_STENCIL
  const unsigned kEnableRawAndStructuredBuffers = 0x00000010; // D3D11_SB_GLOBAL_FLAG_ENABLE_RAW_AND_STRUCTURED_BUFFERS
  const unsigned kEnableMinPrecision            = 0x00000020; // D3D11_1_SB_GLOBAL_FLAG_ENABLE_MINIMUM_PRECISION
  const unsigned kEnableDoubleExtensions        = 0x00000040; // D3D11_1_SB_GLOBAL_FLAG_ENABLE_DOUBLE_EXTENSIONS
  const unsigned kEnableMSAD                    = 0x00000080; // D3D11_1_SB_GLOBAL_FLAG_ENABLE_SHADER_EXTENSIONS
  const unsigned kAllResourcesBound             = 0x00000100; // D3D12_SB_GLOBAL_FLAG_ALL_RESOURCES_BOUND

  const unsigned kNumOutputStreams = 4;
  const unsigned kNumClipPlanes = 6;

  // TODO: move these to appropriate places (ShaderModel.cpp?)
  const unsigned kMaxTempRegCount = 4096;         // DXBC only
  const unsigned kMaxCBufferSize = 4096;
  const unsigned kMaxStructBufferStride = 2048;
  const unsigned kMaxHSOutputControlPointsTotalScalars = 3968;
  const unsigned kMaxHSOutputPatchConstantTotalScalars = 32*4;
  const unsigned kMaxSignatureTotalVectors = 32;
  const unsigned kMaxOutputTotalScalars = kMaxSignatureTotalVectors * 4;
  const unsigned kMaxInputTotalScalars = kMaxSignatureTotalVectors * 4;
  const unsigned kMaxClipOrCullDistanceElementCount = 2;
  const unsigned kMaxClipOrCullDistanceCount = 2 * 4;
  const unsigned kMaxGSOutputVertexCount = 1024;
  const unsigned kMaxGSInstanceCount = 32;
  const unsigned kMaxIAPatchControlPointCount = 32;
  const float kHSMaxTessFactorLowerBound = 1.0f;
  const float kHSMaxTessFactorUpperBound = 64.0f;
  const unsigned kHSDefaultInputControlPointCount = 1;
  const unsigned kMaxCSThreadsPerGroup = 1024;
  const unsigned kMaxCSThreadGroupX	= 1024;
  const unsigned kMaxCSThreadGroupY	= 1024;
  const unsigned kMaxCSThreadGroupZ = 64;
  const unsigned kMinCSThreadGroupX = 1;
  const unsigned kMinCSThreadGroupY = 1;
  const unsigned kMinCSThreadGroupZ = 1;
  const unsigned kMaxCS4XThreadsPerGroup = 768;
  const unsigned kMaxCS4XThreadGroupX	= 768;
  const unsigned kMaxCS4XThreadGroupY	= 768;
  const unsigned kMaxTGSMSize = 8192*4;
  const unsigned kMaxGSOutputTotalScalars = 1024;

  const float kMaxMipLodBias = 15.99f;
  const float kMinMipLodBias = -16.0f;

  const unsigned kResRetStatusIndex = 4;

  enum class ComponentType : uint8_t { 
    Invalid = 0,
    I1, I16, U16, I32, U32, I64, U64,
    F16, F32, F64,
    SNormF16, UNormF16, SNormF32, UNormF32, SNormF64, UNormF64,
    LastEntry };

  enum class InterpolationMode : uint8_t {
    Undefined                   = 0,
    Constant                    = 1,
    Linear                      = 2,
    LinearCentroid              = 3,
    LinearNoperspective         = 4,
    LinearNoperspectiveCentroid = 5,
    LinearSample                = 6,
    LinearNoperspectiveSample   = 7,
    Invalid                     = 8
  };

  // size of each scalar type in signature element in bits
  enum class SignatureDataWidth : uint8_t {
    Undefined = 0,
    Bits16 = 16,
    Bits32 = 32,
  };

  enum class SignatureKind {
    Invalid = 0,
    Input,
    Output,
    PatchConstant,
  };

  enum class ShaderKind {
    Pixel = 0,
    Vertex,
    Geometry,
    Hull,
    Domain,
    Compute,
    Library,
    RayGeneration,
    Intersection,
    AnyHit,
    ClosestHit,
    Miss,
    Callable,
    Invalid,
  };

  /* <py::lines('SemanticKind-ENUM')>hctdb_instrhelp.get_enum_decl("SemanticKind", hide_val=True, sort_val=False)</py>*/
  // SemanticKind-ENUM:BEGIN
  // Semantic kind; Arbitrary or specific system value.
  enum class SemanticKind : unsigned {
    Arbitrary,
    VertexID,
    InstanceID,
    Position,
    RenderTargetArrayIndex,
    ViewPortArrayIndex,
    ClipDistance,
    CullDistance,
    OutputControlPointID,
    DomainLocation,
    PrimitiveID,
    GSInstanceID,
    SampleIndex,
    IsFrontFace,
    Coverage,
    InnerCoverage,
    Target,
    Depth,
    DepthLessEqual,
    DepthGreaterEqual,
    StencilRef,
    DispatchThreadID,
    GroupID,
    GroupIndex,
    GroupThreadID,
    TessFactor,
    InsideTessFactor,
    ViewID,
    Barycentrics,
    Invalid,
  };
  // SemanticKind-ENUM:END

  /* <py::lines('SigPointKind-ENUM')>hctdb_instrhelp.get_enum_decl("SigPointKind", hide_val=True, sort_val=False)</py>*/
  // SigPointKind-ENUM:BEGIN
  // Signature Point is more specific than shader stage or signature as it is unique in both stage and item dimensionality or frequency.
  enum class SigPointKind : unsigned {
    VSIn, // Ordinary Vertex Shader input from Input Assembler
    VSOut, // Ordinary Vertex Shader output that may feed Rasterizer
    PCIn, // Patch Constant function non-patch inputs
    HSIn, // Hull Shader function non-patch inputs
    HSCPIn, // Hull Shader patch inputs - Control Points
    HSCPOut, // Hull Shader function output - Control Point
    PCOut, // Patch Constant function output - Patch Constant data passed to Domain Shader
    DSIn, // Domain Shader regular input - Patch Constant data plus system values
    DSCPIn, // Domain Shader patch input - Control Points
    DSOut, // Domain Shader output - vertex data that may feed Rasterizer
    GSVIn, // Geometry Shader vertex input - qualified with primitive type
    GSIn, // Geometry Shader non-vertex inputs (system values)
    GSOut, // Geometry Shader output - vertex data that may feed Rasterizer
    PSIn, // Pixel Shader input
    PSOut, // Pixel Shader output
    CSIn, // Compute Shader input
    Invalid,
  };
  // SigPointKind-ENUM:END

  /* <py::lines('SemanticInterpretationKind-ENUM')>hctdb_instrhelp.get_enum_decl("SemanticInterpretationKind", hide_val=True, sort_val=False)</py>*/
  // SemanticInterpretationKind-ENUM:BEGIN
  // Defines how a semantic is interpreted at a particular SignaturePoint
  enum class SemanticInterpretationKind : unsigned {
    NA, // Not Available
    SV, // Normal System Value
    SGV, // System Generated Value (sorted last)
    Arb, // Treated as Arbitrary
    NotInSig, // Not included in signature (intrinsic access)
    NotPacked, // Included in signature, but does not contribute to packing
    Target, // Special handling for SV_Target
    TessFactor, // Special handling for tessellation factors
    Shadow, // Shadow element must be added to a signature for compatibility
    Invalid,
  };
  // SemanticInterpretationKind-ENUM:END

  /* <py::lines('PackingKind-ENUM')>hctdb_instrhelp.get_enum_decl("PackingKind", hide_val=True, sort_val=False)</py>*/
  // PackingKind-ENUM:BEGIN
  // Kind of signature point
  enum class PackingKind : unsigned {
    None, // No packing should be performed
    InputAssembler, // Vertex Shader input from Input Assembler
    Vertex, // Vertex that may feed the Rasterizer
    PatchConstant, // Patch constant signature
    Target, // Render Target (Pixel Shader Output)
    Invalid,
  };
  // PackingKind-ENUM:END

  /* <py::lines('FPDenormMode-ENUM')>hctdb_instrhelp.get_enum_decl("Float32DenormMode", hide_val=False, sort_val=False)</py>*/
  // FPDenormMode-ENUM:BEGIN
  // float32 denorm behavior
  enum class Float32DenormMode : unsigned {
    Any = 0, // Undefined behavior for denormal numbers
    Preserve = 1, // Preserve both input and output
    FTZ = 2, // Preserve denormal inputs. Flush denorm outputs
    Reserve3 = 3, // Reserved Value. Not used for now
    Reserve4 = 4, // Reserved Value. Not used for now
    Reserve5 = 5, // Reserved Value. Not used for now
    Reserve6 = 6, // Reserved Value. Not used for now
    Reserve7 = 7, // Reserved Value. Not used for now
  };
  // FPDenormMode-ENUM:END

  enum class PackingStrategy : unsigned {
    Default = 0, // Choose default packing algorithm based on target (currently PrefixStable)
    PrefixStable, // Maintain assumption that all elements are packed in order and stable as new elements are added.
    Optimized, // Optimize packing of all elements together (all elements must be present, in the same order, for identical placement of any individual element)
    Invalid,
  };

  enum class SamplerKind : unsigned {
    Default = 0,
    Comparison,
    Mono,
    Invalid,
  };

  enum class ResourceClass {
    SRV = 0,
    UAV,
    CBuffer,
    Sampler,
    Invalid
  };

  enum class ResourceKind : unsigned {
    Invalid = 0,
    Texture1D,
    Texture2D,
    Texture2DMS,
    Texture3D,
    TextureCube,
    Texture1DArray,
    Texture2DArray,
    Texture2DMSArray,
    TextureCubeArray,
    TypedBuffer,
    RawBuffer,
    StructuredBuffer,
    CBuffer,
    Sampler,
    TBuffer,
    RTAccelerationStructure,
    NumEntries,
  };

  // TODO: change opcodes.
  /* <py::lines('OPCODE-ENUM')>hctdb_instrhelp.get_enum_decl("OpCode")</py>*/
  // OPCODE-ENUM:BEGIN
  // Enumeration for operations specified by DXIL
  enum class OpCode : unsigned {
    // AnyHit Terminals
    AcceptHitAndEndSearch = 156, // Used in an any hit shader to abort the ray query and the intersection shader (if any). The current hit is committed and execution passes to the closest hit shader with the closest hit recorded so far
    IgnoreHit = 155, // Used in an any hit shader to reject an intersection and terminate the shader
  
    // Binary float
    FMax = 35, // returns a if a >= b, else b
    FMin = 36, // returns a if a < b, else b
  
    // Binary int with two outputs
    IMul = 41, // multiply of 32-bit operands to produce the correct full 64-bit result.
  
    // Binary int
    IMax = 37, // IMax(a,b) returns a if a > b, else b
    IMin = 38, // IMin(a,b) returns a if a < b, else b
  
    // Binary uint with carry or borrow
    UAddc = 44, // unsigned add of 32-bit operand with the carry
    USubb = 45, // unsigned subtract of 32-bit operands with the borrow
  
    // Binary uint with two outputs
    UDiv = 43, // unsigned divide of the 32-bit operand src0 by the 32-bit operand src1.
    UMul = 42, // multiply of 32-bit operands to produce the correct full 64-bit result.
  
    // Binary uint
    UMax = 39, // unsigned integer maximum. UMax(a,b) = a > b ? a : b
    UMin = 40, // unsigned integer minimum. UMin(a,b) = a < b ? a : b
  
    // Bitcasts with different sizes
    BitcastF16toI16 = 125, // bitcast between different sizes
    BitcastF32toI32 = 127, // bitcast between different sizes
    BitcastF64toI64 = 129, // bitcast between different sizes
    BitcastI16toF16 = 124, // bitcast between different sizes
    BitcastI32toF32 = 126, // bitcast between different sizes
    BitcastI64toF64 = 128, // bitcast between different sizes
  
    // Compute shader
    FlattenedThreadIdInGroup = 96, // provides a flattened index for a given thread within a given group (SV_GroupIndex)
    GroupId = 94, // reads the group ID (SV_GroupID)
    ThreadId = 93, // reads the thread ID
    ThreadIdInGroup = 95, // reads the thread ID within the group (SV_GroupThreadID)
  
    // Domain and hull shader
    LoadOutputControlPoint = 103, // LoadOutputControlPoint
    LoadPatchConstant = 104, // LoadPatchConstant
  
    // Domain shader
    DomainLocation = 105, // DomainLocation
  
    // Dot
    Dot2 = 54, // Two-dimensional vector dot-product
    Dot3 = 55, // Three-dimensional vector dot-product
    Dot4 = 56, // Four-dimensional vector dot-product
  
    // Double precision
    LegacyDoubleToFloat = 132, // legacy fuction to convert double to float
    LegacyDoubleToSInt32 = 133, // legacy fuction to convert double to int32
    LegacyDoubleToUInt32 = 134, // legacy fuction to convert double to uint32
    MakeDouble = 101, // creates a double value
    SplitDouble = 102, // splits a double into low and high parts
  
    // Geometry shader
    CutStream = 98, // completes the current primitive topology at the specified stream
    EmitStream = 97, // emits a vertex to a given stream
    EmitThenCutStream = 99, // equivalent to an EmitStream followed by a CutStream
    GSInstanceID = 100, // GSInstanceID
  
    // Graphics shader
    ViewID = 138, // returns the view index
  
    // Hull shader
    OutputControlPointID = 107, // OutputControlPointID
    StorePatchConstant = 106, // StorePatchConstant
  
    // Hull, Domain and Geometry shaders
    PrimitiveID = 108, // PrimitiveID
  
    // Indirect Shader Invocation
    CallShader = 159, // Call a shader in the callable shader table supplied through the DispatchRays() API
    ReportHit = 158, // returns true if hit was accepted
    TraceRay = 157, // returns the view index
  
    // Legacy floating-point
    LegacyF16ToF32 = 131, // legacy fuction to convert half (f16) to float (f32) (this is not related to min-precision)
    LegacyF32ToF16 = 130, // legacy fuction to convert float (f32) to half (f16) (this is not related to min-precision)
  
    // Library create handle from resource struct (like HL intrinsic)
    CreateHandleForLib = 160, // create resource handle from resource struct for library
  
    // Other
    CycleCounterLegacy = 109, // CycleCounterLegacy
  
    // Pixel shader
    AttributeAtVertex = 137, // returns the values of the attributes at the vertex.
    CalculateLOD = 81, // calculates the level of detail
    Coverage = 91, // returns the coverage mask input in a pixel shader
    DerivCoarseX = 83, // computes the rate of change per stamp in x direction.
    DerivCoarseY = 84, // computes the rate of change per stamp in y direction.
    DerivFineX = 85, // computes the rate of change per pixel in x direction.
    DerivFineY = 86, // computes the rate of change per pixel in y direction.
    Discard = 82, // discard the current pixel
    EvalCentroid = 89, // evaluates an input attribute at pixel center
    EvalSampleIndex = 88, // evaluates an input attribute at a sample location
    EvalSnapped = 87, // evaluates an input attribute at pixel center with an offset
    InnerCoverage = 92, // returns underestimated coverage input from conservative rasterization in a pixel shader
    SampleIndex = 90, // returns the sample index in a sample-frequency pixel shader
  
    // Quaternary
    Bfi = 53, // Given a bit range from the LSB of a number, places that number of bits in another number at any offset
  
    // Ray Dispatch Arguments
    DispatchRaysDimensions = 146, // The Width and Height values from the D3D12_DISPATCH_RAYS_DESC structure provided to the originating DispatchRays() call.
    DispatchRaysIndex = 145, // The current x and y location within the Width and Height
  
    // Ray Transforms
    ObjectToWorld = 151, // Matrix for transforming from object-space to world-space.
    WorldToObject = 152, // Matrix for transforming from world-space to object-space.
  
    // Ray Vectors
    WorldRayDirection = 148, // The world-space direction for the current ray.
    WorldRayOrigin = 147, // The world-space origin for the current ray.
  
    // Ray object space Vectors
    ObjectRayDirection = 150, // Object-space direction for the current ray.
    ObjectRayOrigin = 149, // Object-space origin for the current ray.
  
    // RayT
    RayTCurrent = 154, // float representing the current parametric ending point for the ray
    RayTMin = 153, // float representing the parametric starting point for the ray.
  
    // Raytracing hit uint System Values
    HitKind = 143, // Returns the value passed as HitKind in ReportIntersection().  If intersection was reported by fixed-function triangle intersection, HitKind will be one of HIT_KIND_TRIANGLE_FRONT_FACE or HIT_KIND_TRIANGLE_BACK_FACE.
  
    // Raytracing object space uint System Values
    InstanceID = 141, // The user-provided InstanceID on the bottom-level acceleration structure instance within the top-level structure
    InstanceIndex = 142, // The autogenerated index of the current instance in the top-level structure
    PrimitiveIndex = 161, // PrimitiveIndex for raytracing shaders
  
    // Raytracing uint System Values
    RayFlags = 144, // uint containing the current ray flags.
  
    // Resources - gather
    TextureGather = 73, // gathers the four texels that would be used in a bi-linear filtering operation
    TextureGatherCmp = 74, // same as TextureGather, except this instrution performs comparison on texels, similar to SampleCmp
  
    // Resources - sample
    RenderTargetGetSampleCount = 77, // gets the number of samples for a render target
    RenderTargetGetSamplePosition = 76, // gets the position of the specified sample
    Sample = 60, // samples a texture
    SampleBias = 61, // samples a texture after applying the input bias to the mipmap level
    SampleCmp = 64, // samples a texture and compares a single component against the specified comparison value
    SampleCmpLevelZero = 65, // samples a texture and compares a single component against the specified comparison value
    SampleGrad = 63, // samples a texture using a gradient to influence the way the sample location is calculated
    SampleLevel = 62, // samples a texture using a mipmap-level offset
    Texture2DMSGetSamplePosition = 75, // gets the position of the specified sample
  
    // Resources
    BufferLoad = 68, // reads from a TypedBuffer
    BufferStore = 69, // writes to a RWTypedBuffer
    BufferUpdateCounter = 70, // atomically increments/decrements the hidden 32-bit counter stored with a Count or Append UAV
    CBufferLoad = 58, // loads a value from a constant buffer resource
    CBufferLoadLegacy = 59, // loads a value from a constant buffer resource
    CheckAccessFullyMapped = 71, // determines whether all values from a Sample, Gather, or Load operation accessed mapped tiles in a tiled resource
    CreateHandle = 57, // creates the handle to a resource
    GetDimensions = 72, // gets texture size information
    RawBufferLoad = 139, // reads from a raw buffer and structured buffer
    RawBufferStore = 140, // writes to a RWByteAddressBuffer or RWStructuredBuffer
    TextureLoad = 66, // reads texel data without any filtering or sampling
    TextureStore = 67, // reads texel data without any filtering or sampling
  
    // Synchronization
    AtomicBinOp = 78, // performs an atomic operation on two operands
    AtomicCompareExchange = 79, // atomic compare and exchange to memory
    Barrier = 80, // inserts a memory barrier in the shader
  
    // Temporary, indexable, input, output registers
    LoadInput = 4, // Loads the value from shader input
    MinPrecXRegLoad = 2, // Helper load operation for minprecision
    MinPrecXRegStore = 3, // Helper store operation for minprecision
    StoreOutput = 5, // Stores the value to shader output
    TempRegLoad = 0, // Helper load operation
    TempRegStore = 1, // Helper store operation
  
    // Tertiary float
    FMad = 46, // floating point multiply & add
    Fma = 47, // fused multiply-add
  
    // Tertiary int
    IMad = 48, // Signed integer multiply & add
    Ibfe = 51, // Integer bitfield extract
    Msad = 50, // masked Sum of Absolute Differences.
  
    // Tertiary uint
    UMad = 49, // Unsigned integer multiply & add
    Ubfe = 52, // Unsigned integer bitfield extract
  
    // Unary float - rounding
    Round_ne = 26, // floating-point round to integral float.
    Round_ni = 27, // floating-point round to integral float.
    Round_pi = 28, // floating-point round to integral float.
    Round_z = 29, // floating-point round to integral float.
  
    // Unary float
    Acos = 15, // Returns the arccosine of the specified value. Input should be a floating-point value within the range of -1 to 1.
    Asin = 16, // Returns the arccosine of the specified value. Input should be a floating-point value within the range of -1 to 1
    Atan = 17, // Returns the arctangent of the specified value. The return value is within the range of -PI/2 to PI/2.
    Cos = 12, // returns cosine(theta) for theta in radians.
    Exp = 21, // returns 2^exponent
    FAbs = 6, // returns the absolute value of the input value.
    Frc = 22, // extract fracitonal component.
    Hcos = 18, // returns the hyperbolic cosine of the specified value.
    Hsin = 19, // returns the hyperbolic sine of the specified value.
    Htan = 20, // returns the hyperbolic tangent of the specified value.
    IsFinite = 10, // Returns true if x is finite, false otherwise.
    IsInf = 9, // Returns true if x is +INF or -INF, false otherwise.
    IsNaN = 8, // Returns true if x is NAN or QNAN, false otherwise.
    IsNormal = 11, // returns IsNormal
    Log = 23, // returns log base 2.
    Rsqrt = 25, // returns reciprocal square root (1 / sqrt(src)
    Saturate = 7, // clamps the result of a single or double precision floating point value to [0.0f...1.0f]
    Sin = 13, // returns sine(theta) for theta in radians.
    Sqrt = 24, // returns square root
    Tan = 14, // returns tan(theta) for theta in radians.
  
    // Unary int
    Bfrev = 30, // Reverses the order of the bits.
    Countbits = 31, // Counts the number of bits in the input integer.
    FirstbitLo = 32, // Returns the location of the first set bit starting from the lowest order bit and working upward.
    FirstbitSHi = 34, // Returns the location of the first set bit from the highest order bit based on the sign.
  
    // Unary uint
    FirstbitHi = 33, // Returns the location of the first set bit starting from the highest order bit and working downward.
  
    // Wave
    QuadOp = 123, // returns the result of a quad-level operation
    QuadReadLaneAt = 122, // reads from a lane in the quad
    WaveActiveAllEqual = 115, // returns 1 if all the lanes have the same value
    WaveActiveBallot = 116, // returns a struct with a bit set for each lane where the condition is true
    WaveActiveBit = 120, // returns the result of the operation across all lanes
    WaveActiveOp = 119, // returns the result the operation across waves
    WaveAllBitCount = 135, // returns the count of bits set to 1 across the wave
    WaveAllTrue = 114, // returns 1 if all the lanes evaluate the value to true
    WaveAnyTrue = 113, // returns 1 if any of the lane evaluates the value to true
    WaveGetLaneCount = 112, // returns the number of lanes in the wave
    WaveGetLaneIndex = 111, // returns the index of the current lane in the wave
    WaveIsFirstLane = 110, // returns 1 for the first lane in the wave
    WavePrefixBitCount = 136, // returns the count of bits set to 1 on prior lanes
    WavePrefixOp = 121, // returns the result of the operation on prior lanes
    WaveReadLaneAt = 117, // returns the value from the specified lane
    WaveReadLaneFirst = 118, // returns the value from the first lane
  
    NumOpCodes_Dxil_1_0 = 137,
    NumOpCodes_Dxil_1_1 = 139,
    NumOpCodes_Dxil_1_2 = 141,
    NumOpCodes_Dxil_1_3 = 162,
  
    NumOpCodes = 162 // exclusive last value of enumeration
  };
  // OPCODE-ENUM:END

  /* <py::lines('OPCODECLASS-ENUM')>hctdb_instrhelp.get_enum_decl("OpCodeClass")</py>*/
  // OPCODECLASS-ENUM:BEGIN
  // Groups for DXIL operations with equivalent function templates
  enum class OpCodeClass : unsigned {
    // AnyHit Terminals
    AcceptHitAndEndSearch,
    IgnoreHit,
  
    // Binary uint with carry or borrow
    BinaryWithCarryOrBorrow,
  
    // Binary uint with two outputs
    BinaryWithTwoOuts,
  
    // Binary uint
    Binary,
  
    // Bitcasts with different sizes
    BitcastF16toI16,
    BitcastF32toI32,
    BitcastF64toI64,
    BitcastI16toF16,
    BitcastI32toF32,
    BitcastI64toF64,
  
    // Compute shader
    FlattenedThreadIdInGroup,
    GroupId,
    ThreadId,
    ThreadIdInGroup,
  
    // Domain and hull shader
    LoadOutputControlPoint,
    LoadPatchConstant,
  
    // Domain shader
    DomainLocation,
  
    // Dot
    Dot2,
    Dot3,
    Dot4,
  
    // Double precision
    LegacyDoubleToFloat,
    LegacyDoubleToSInt32,
    LegacyDoubleToUInt32,
    MakeDouble,
    SplitDouble,
  
    // Geometry shader
    CutStream,
    EmitStream,
    EmitThenCutStream,
    GSInstanceID,
  
    // Graphics shader
    ViewID,
  
    // Hull shader
    OutputControlPointID,
    StorePatchConstant,
  
    // Hull, Domain and Geometry shaders
    PrimitiveID,
  
    // Indirect Shader Invocation
    CallShader,
    ReportHit,
    TraceRay,
  
    // LLVM Instructions
    LlvmInst,
  
    // Legacy floating-point
    LegacyF16ToF32,
    LegacyF32ToF16,
  
    // Library create handle from resource struct (like HL intrinsic)
    CreateHandleForLib,
  
    // Other
    CycleCounterLegacy,
  
    // Pixel shader
    AttributeAtVertex,
    CalculateLOD,
    Coverage,
    Discard,
    EvalCentroid,
    EvalSampleIndex,
    EvalSnapped,
    InnerCoverage,
    SampleIndex,
    Unary,
  
    // Quaternary
    Quaternary,
  
    // Ray Dispatch Arguments
    DispatchRaysDimensions,
    DispatchRaysIndex,
  
    // Ray Transforms
    ObjectToWorld,
    WorldToObject,
  
    // Ray Vectors
    WorldRayDirection,
    WorldRayOrigin,
  
    // Ray object space Vectors
    ObjectRayDirection,
    ObjectRayOrigin,
  
    // RayT
    RayTCurrent,
    RayTMin,
  
    // Raytracing hit uint System Values
    HitKind,
  
    // Raytracing object space uint System Values
    InstanceID,
    InstanceIndex,
    PrimitiveIndex,
  
    // Raytracing uint System Values
    RayFlags,
  
    // Resources - gather
    TextureGather,
    TextureGatherCmp,
  
    // Resources - sample
    RenderTargetGetSampleCount,
    RenderTargetGetSamplePosition,
    Sample,
    SampleBias,
    SampleCmp,
    SampleCmpLevelZero,
    SampleGrad,
    SampleLevel,
    Texture2DMSGetSamplePosition,
  
    // Resources
    BufferLoad,
    BufferStore,
    BufferUpdateCounter,
    CBufferLoad,
    CBufferLoadLegacy,
    CheckAccessFullyMapped,
    CreateHandle,
    GetDimensions,
    RawBufferLoad,
    RawBufferStore,
    TextureLoad,
    TextureStore,
  
    // Synchronization
    AtomicBinOp,
    AtomicCompareExchange,
    Barrier,
  
    // Temporary, indexable, input, output registers
    LoadInput,
    MinPrecXRegLoad,
    MinPrecXRegStore,
    StoreOutput,
    TempRegLoad,
    TempRegStore,
  
    // Tertiary uint
    Tertiary,
  
    // Unary float
    IsSpecialFloat,
  
    // Unary int
    UnaryBits,
  
    // Wave
    QuadOp,
    QuadReadLaneAt,
    WaveActiveAllEqual,
    WaveActiveBallot,
    WaveActiveBit,
    WaveActiveOp,
    WaveAllOp,
    WaveAllTrue,
    WaveAnyTrue,
    WaveGetLaneCount,
    WaveGetLaneIndex,
    WaveIsFirstLane,
    WavePrefixOp,
    WaveReadLaneAt,
    WaveReadLaneFirst,
  
    NumOpClasses_Dxil_1_0 = 93,
    NumOpClasses_Dxil_1_1 = 95,
    NumOpClasses_Dxil_1_2 = 97,
    NumOpClasses_Dxil_1_3 = 118,
  
    NumOpClasses = 118 // exclusive last value of enumeration
  };
  // OPCODECLASS-ENUM:END

  // Operand Index for every OpCodeClass.
  namespace OperandIndex {
    // Opcode is always operand 0.
    const unsigned kOpcodeIdx = 0;

    // Unary operators.
    const unsigned kUnarySrc0OpIdx = 1;

    // Binary operators.
    const unsigned kBinarySrc0OpIdx = 1;
    const unsigned kBinarySrc1OpIdx = 2;

    // Trinary operators.
    const unsigned kTrinarySrc0OpIdx = 1;
    const unsigned kTrinarySrc1OpIdx = 2;
    const unsigned kTrinarySrc2OpIdx = 3;

    // LoadInput.
    const unsigned kLoadInputIDOpIdx = 1;
    const unsigned kLoadInputRowOpIdx = 2;
    const unsigned kLoadInputColOpIdx = 3;
    const unsigned kLoadInputVertexIDOpIdx = 4;

    // StoreOutput.
    const unsigned kStoreOutputIDOpIdx = 1;
    const unsigned kStoreOutputRowOpIdx = 2;
    const unsigned kStoreOutputColOpIdx = 3;
    const unsigned kStoreOutputValOpIdx = 4;

    // DomainLocation.
    const unsigned kDomainLocationColOpIdx = 1;

    // BufferLoad.
    const unsigned kBufferLoadHandleOpIdx = 1;
    const unsigned kBufferLoadCoord0OpIdx = 2;
    const unsigned kBufferLoadCoord1OpIdx = 3;

    // BufferStore.
    const unsigned kBufferStoreHandleOpIdx = 1;
    const unsigned kBufferStoreCoord0OpIdx = 2;
    const unsigned kBufferStoreCoord1OpIdx = 3;
    const unsigned kBufferStoreVal0OpIdx = 4;
    const unsigned kBufferStoreVal1OpIdx = 5;
    const unsigned kBufferStoreVal2OpIdx = 6;
    const unsigned kBufferStoreVal3OpIdx = 7;
    const unsigned kBufferStoreMaskOpIdx = 8;

    // RawBufferLoad.
    const unsigned kRawBufferLoadHandleOpIdx        = 1;
    const unsigned kRawBufferLoadIndexOpIdx         = 2;
    const unsigned kRawBufferLoadElementOffsetOpIdx = 3;
    const unsigned kRawBufferLoadMaskOpIdx          = 4;
    const unsigned kRawBufferLoadAlignmentOpIdx     = 5;

    // RawBufferStore
    const unsigned kRawBufferStoreHandleOpIdx = 1;
    const unsigned kRawBufferStoreIndexOpIdx = 2;
    const unsigned kRawBufferStoreElementOffsetOpIdx = 3;
    const unsigned kRawBufferStoreVal0OpIdx = 4;
    const unsigned kRawBufferStoreVal1OpIdx = 5;
    const unsigned kRawBufferStoreVal2OpIdx = 6;
    const unsigned kRawBufferStoreVal3OpIdx = 7;
    const unsigned kRawBufferStoreMaskOpIdx = 8;
    const unsigned kRawBufferStoreAlignmentOpIdx = 8;

    // TextureStore.
    const unsigned kTextureStoreHandleOpIdx = 1;
    const unsigned kTextureStoreCoord0OpIdx = 2;
    const unsigned kTextureStoreCoord1OpIdx = 3;
    const unsigned kTextureStoreCoord2OpIdx = 4;
    const unsigned kTextureStoreVal0OpIdx = 5;
    const unsigned kTextureStoreVal1OpIdx = 6;
    const unsigned kTextureStoreVal2OpIdx = 7;
    const unsigned kTextureStoreVal3OpIdx = 8;
    const unsigned kTextureStoreMaskOpIdx = 9;

    // TextureGather.
    const unsigned kTextureGatherTexHandleOpIdx = 1;
    const unsigned kTextureGatherSamplerHandleOpIdx = 2;
    const unsigned kTextureGatherCoord0OpIdx = 3;
    const unsigned kTextureGatherCoord1OpIdx = 4;
    const unsigned kTextureGatherCoord2OpIdx = 5;
    const unsigned kTextureGatherCoord3OpIdx = 6;
    const unsigned kTextureGatherOffset0OpIdx = 7;
    const unsigned kTextureGatherOffset1OpIdx = 8;
    const unsigned kTextureGatherOffset2OpIdx = 9;
    const unsigned kTextureGatherChannelOpIdx = 10;
    // TextureGatherCmp.
    const unsigned kTextureGatherCmpCmpValOpIdx = 11;

    // TextureSample.
    const unsigned kTextureSampleTexHandleOpIdx = 1;
    const unsigned kTextureSampleSamplerHandleOpIdx = 2;
    const unsigned kTextureSampleCoord0OpIdx = 3;
    const unsigned kTextureSampleCoord1OpIdx = 4;
    const unsigned kTextureSampleCoord2OpIdx = 5;
    const unsigned kTextureSampleCoord3OpIdx = 6;
    const unsigned kTextureSampleOffset0OpIdx = 7;
    const unsigned kTextureSampleOffset1OpIdx = 8;
    const unsigned kTextureSampleOffset2OpIdx = 9;
    const unsigned kTextureSampleClampOpIdx = 10;

    // AtomicBinOp.
    const unsigned kAtomicBinOpCoord0OpIdx = 3;
    const unsigned kAtomicBinOpCoord1OpIdx = 4;
    const unsigned kAtomicBinOpCoord2OpIdx = 5;

    // AtomicCmpExchange.
    const unsigned kAtomicCmpExchangeCoord0OpIdx = 2;
    const unsigned kAtomicCmpExchangeCoord1OpIdx = 3;
    const unsigned kAtomicCmpExchangeCoord2OpIdx = 4;

    // CreateHandle
    const unsigned kCreateHandleResClassOpIdx = 1;
    const unsigned kCreateHandleResIDOpIdx = 2;
    const unsigned kCreateHandleResIndexOpIdx = 3;
    const unsigned kCreateHandleIsUniformOpIdx = 4;

    // CreateHandleFromResource
    const unsigned kCreateHandleForLibResOpIdx = 1;

    // TraceRay
    const unsigned kTraceRayRayDescOpIdx = 7;
    const unsigned kTraceRayPayloadOpIdx = 15;
    const unsigned kTraceRayNumOp = 16;


    // Emit/Cut
    const unsigned kStreamEmitCutIDOpIdx = 1;
    // TODO: add operand index for all the OpCodeClass.
  }

  // Atomic binary operation kind.
  enum class AtomicBinOpCode : unsigned {
    Add,
    And,
    Or,
    Xor,
    IMin,
    IMax,
    UMin,
    UMax,
    Exchange,
    Invalid           // Must be last.
  };

  // Barrier/fence modes.
  enum class BarrierMode : unsigned {
    SyncThreadGroup       = 0x00000001,
    UAVFenceGlobal        = 0x00000002,
    UAVFenceThreadGroup   = 0x00000004,
    TGSMFence             = 0x00000008,
  };

  // Address space.
  const unsigned kDefaultAddrSpace = 0;
  const unsigned kDeviceMemoryAddrSpace = 1;
  const unsigned kCBufferAddrSpace = 2;
  const unsigned kTGSMAddrSpace = 3;
  const unsigned kGenericPointerAddrSpace = 4;
  const unsigned kImmediateCBufferAddrSpace = 5;

  // Input primitive.
  enum class InputPrimitive : unsigned {
    Undefined = 0,
    Point = 1,
    Line = 2,
    Triangle = 3,
    Reserved4 = 4,
    Reserved5 = 5,
    LineWithAdjacency = 6,
    TriangleWithAdjacency = 7,
    ControlPointPatch1 = 8,
    ControlPointPatch2 = 9,
    ControlPointPatch3 = 10,
    ControlPointPatch4 = 11,
    ControlPointPatch5 = 12,
    ControlPointPatch6 = 13,
    ControlPointPatch7 = 14,
    ControlPointPatch8 = 15,
    ControlPointPatch9 = 16,
    ControlPointPatch10 = 17,
    ControlPointPatch11 = 18,
    ControlPointPatch12 = 19,
    ControlPointPatch13 = 20,
    ControlPointPatch14 = 21,
    ControlPointPatch15 = 22,
    ControlPointPatch16 = 23,
    ControlPointPatch17 = 24,
    ControlPointPatch18 = 25,
    ControlPointPatch19 = 26,
    ControlPointPatch20 = 27,
    ControlPointPatch21 = 28,
    ControlPointPatch22 = 29,
    ControlPointPatch23 = 30,
    ControlPointPatch24 = 31,
    ControlPointPatch25 = 32,
    ControlPointPatch26 = 33,
    ControlPointPatch27 = 34,
    ControlPointPatch28 = 35,
    ControlPointPatch29 = 36,
    ControlPointPatch30 = 37,
    ControlPointPatch31 = 38,
    ControlPointPatch32 = 39,

    LastEntry,
  };

  // Primitive topology.
  enum class PrimitiveTopology : unsigned {
    Undefined = 0,
    PointList = 1,
    LineList = 2,
    LineStrip = 3,
    TriangleList = 4,
    TriangleStrip = 5,

    LastEntry,
  };

  enum class TessellatorDomain
  {
    Undefined = 0,
    IsoLine = 1,
    Tri = 2,
    Quad = 3,

    LastEntry,
  };

  enum class TessellatorOutputPrimitive
  {
    Undefined = 0,
    Point = 1,
    Line = 2,
    TriangleCW = 3,
    TriangleCCW = 4,

    LastEntry,
  };

  // Tessellator partitioning.
  enum class TessellatorPartitioning : unsigned {
    Undefined = 0,
    Integer,
    Pow2,
    FractionalOdd,
    FractionalEven,

    LastEntry,
  };

  // Kind of quad-level operation
  enum class QuadOpKind {
    ReadAcrossX = 0, // returns the value from the other lane in the quad in the horizontal direction
    ReadAcrossY = 1, // returns the value from the other lane in the quad in the vertical direction
    ReadAcrossDiagonal = 2, // returns the value from the lane across the quad in horizontal and vertical direction
  };

  /* <py::lines('WAVEBITOPKIND-ENUM')>hctdb_instrhelp.get_enum_decl("WaveBitOpKind")</py>*/
  // WAVEBITOPKIND-ENUM:BEGIN
  // Kind of bitwise cross-lane operation
  enum class WaveBitOpKind : unsigned {
    And = 0, // bitwise and of values
    Or = 1, // bitwise or of values
    Xor = 2, // bitwise xor of values
  };
  // WAVEBITOPKIND-ENUM:END

  /* <py::lines('WAVEOPKIND-ENUM')>hctdb_instrhelp.get_enum_decl("WaveOpKind")</py>*/
  // WAVEOPKIND-ENUM:BEGIN
  // Kind of cross-lane operation
  enum class WaveOpKind : unsigned {
    Max = 3, // maximum value
    Min = 2, // minimum value
    Product = 1, // product of values
    Sum = 0, // sum of values
  };
  // WAVEOPKIND-ENUM:END

  /* <py::lines('SIGNEDOPKIND-ENUM')>hctdb_instrhelp.get_enum_decl("SignedOpKind")</py>*/
  // SIGNEDOPKIND-ENUM:BEGIN
  // Sign vs. unsigned operands for operation
  enum class SignedOpKind : unsigned {
    Signed = 0, // signed integer or floating-point operands
    Unsigned = 1, // unsigned integer operands
  };
  // SIGNEDOPKIND-ENUM:END

  // Kind of control flow hint
  enum class ControlFlowHint : unsigned {
    Undefined = 0,
    Branch = 1,
    Flatten = 2,
    FastOpt = 3,
    AllowUavCondition = 4,
    ForceCase = 5,
    Call = 6,
    // Loop and Unroll is using llvm.loop.unroll Metadata.

    LastEntry,
  };

  // XYZW component mask.
  const uint8_t kCompMask_X     = 0x1;
  const uint8_t kCompMask_Y     = 0x2;
  const uint8_t kCompMask_Z     = 0x4;
  const uint8_t kCompMask_W     = 0x8;
  const uint8_t kCompMask_All   = 0xF;


  enum class LowPrecisionMode {
    Undefined = 0,
    UseMinPrecision,
    UseNativeLowPrecision
  };

  // Corresponds to HIT_FLAG_* in HLSL
  enum class RayFlag : uint8_t {
    None = 0x00,
    ForceOpaque = 0x01,
    ForceNonOpaque = 0x02,
    AcceptFirstHitAndEndSearch = 0x04,
    SkipClosestHitShader = 0x08,
    CullBackFacingTriangles = 0x10,
    CullFrontFacingTriangles = 0x20,
    CullOpaque = 0x40,
    CullNonOpaque = 0x80,
  };

  // Corresponds to HIT_KIND_* in HLSL
  enum class HitKind : uint8_t {
    None = 0x00,
    TriangleFrontFace = 0xFE,
    TriangleBackFace = 0xFF,
  };


  extern const char* kLegacyLayoutString;
  extern const char* kNewLayoutString;
  extern const char* kFP32DenormKindString;
  extern const char* kFP32DenormValueAnyString;
  extern const char* kFP32DenormValuePreserveString;
  extern const char* kFP32DenormValueFtzString;

} // namespace DXIL

} // namespace hlsl
