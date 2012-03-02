#ifndef SPRIG_WAVE_COMPILER_GCC_HPP
#define SPRIG_WAVE_COMPILER_GCC_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <sprig/wave/config.hpp>

#ifdef SPRIG_WAVE_GCC

	//
	// SPRIG_WAVE_MACROS_[N]
	//
#	define SPRIG_WAVE_MACROS_0(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef NDEBUG
#		define SPRIG_WAVE_MACROS_1(OPT) SPRIG_WAVE_MACROS_DEF(OPT, NDEBUG)
#	else
#		define SPRIG_WAVE_MACROS_1(OPT) SPRIG_WAVE_MACROS_NDEF(OPT, NDEBUG)
#	endif
#	define SPRIG_WAVE_MACROS_2(OPT) SPRIG_WAVE_MACROS_REM(OPT, "�f�o�b�O�ł������[�X�ł�")

#	define SPRIG_WAVE_MACROS_3(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef __GNUC__
#		define SPRIG_WAVE_MACROS_4(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __GNUC__)
#	else
#		define SPRIG_WAVE_MACROS_4(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __GNUC__)
#	endif
#	ifdef __GNUC_MINOR__
#		define SPRIG_WAVE_MACROS_5(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __GNUC_MINOR__)
#	else
#		define SPRIG_WAVE_MACROS_5(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __GNUC_MINOR__)
#	endif
#	ifdef __GNUC_PATCHLEVEL__
#		define SPRIG_WAVE_MACROS_6(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __GNUC_PATCHLEVEL__)
#	else
#		define SPRIG_WAVE_MACROS_6(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __GNUC_PATCHLEVEL__)
#	endif
#	ifdef __VERSION__
#		define SPRIG_WAVE_MACROS_7(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __VERSION__)
#	else
#		define SPRIG_WAVE_MACROS_7(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __VERSION__)
#	endif
#	define SPRIG_WAVE_MACROS_8(OPT) SPRIG_WAVE_MACROS_REM(OPT, "GNU C++")

#	define SPRIG_WAVE_MACROS_9(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef __SIZE_TYPE__
#		define SPRIG_WAVE_MACROS_10(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __SIZE_TYPE__)
#	else
#		define SPRIG_WAVE_MACROS_10(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __SIZE_TYPE__)
#	endif
#	ifdef __PTRDIFF_TYPE__
#		define SPRIG_WAVE_MACROS_11(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __PTRDIFF_TYPE__)
#	else
#		define SPRIG_WAVE_MACROS_11(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __PTRDIFF_TYPE__)
#	endif
#	ifdef __WCHAR_TYPE__
#		define SPRIG_WAVE_MACROS_12(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __WCHAR_TYPE__)
#	else
#		define SPRIG_WAVE_MACROS_12(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __WCHAR_TYPE__)
#	endif
#	ifdef __WINT_TYPE__
#		define SPRIG_WAVE_MACROS_13(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __WINT_TYPE__)
#	else
#		define SPRIG_WAVE_MACROS_13(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __WINT_TYPE__)
#	endif
#	define SPRIG_WAVE_MACROS_14(OPT) SPRIG_WAVE_MACROS_REM(OPT, "�^��`")

#	define SPRIG_WAVE_MACROS_15(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef __CHAR_BIT__
#		define SPRIG_WAVE_MACROS_16(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __CHAR_BIT__)
#	else
#		define SPRIG_WAVE_MACROS_16(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __CHAR_BIT__)
#	endif
#	define SPRIG_WAVE_MACROS_17(OPT) SPRIG_WAVE_MACROS_REM(OPT, "char �̃r�b�g��")

#	define SPRIG_WAVE_MACROS_18(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef __SHRT_MAX__
#		define SPRIG_WAVE_MACROS_19(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __SHRT_MAX__)
#	else
#		define SPRIG_WAVE_MACROS_19(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __SHRT_MAX__)
#	endif
#	ifdef __INT_MAX__
#		define SPRIG_WAVE_MACROS_20(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __INT_MAX__)
#	else
#		define SPRIG_WAVE_MACROS_20(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __INT_MAX__)
#	endif
#	ifdef __LONG_MAX__
#		define SPRIG_WAVE_MACROS_21(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __LONG_MAX__)
#	else
#		define SPRIG_WAVE_MACROS_21(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __LONG_MAX__)
#	endif
#	ifdef __LONG_LONG_MAX__
#		define SPRIG_WAVE_MACROS_22(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __LONG_LONG_MAX__)
#	else
#		define SPRIG_WAVE_MACROS_22(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __LONG_LONG_MAX__)
#	endif
#	ifdef __SCHAR_MAX__
#		define SPRIG_WAVE_MACROS_23(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __SCHAR_MAX__)
#	else
#		define SPRIG_WAVE_MACROS_23(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __SCHAR_MAX__)
#	endif
#	ifdef __WCHAR_MAX__
#		define SPRIG_WAVE_MACROS_24(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __WCHAR_MAX__)
#	else
#		define SPRIG_WAVE_MACROS_24(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __WCHAR_MAX__)
#	endif
#	define SPRIG_WAVE_MACROS_25(OPT) SPRIG_WAVE_MACROS_REM(OPT, "�����^�̍ő�l")

#	define SPRIG_WAVE_MACROS_26(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef __FLT_DIG__
#		define SPRIG_WAVE_MACROS_27(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __FLT_DIG__)
#	else
#		define SPRIG_WAVE_MACROS_27(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __FLT_DIG__)
#	endif
#	ifdef __FLT_MIN__
#		define SPRIG_WAVE_MACROS_28(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __FLT_MIN__)
#	else
#		define SPRIG_WAVE_MACROS_28(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __FLT_MIN__)
#	endif
#	ifdef __FLT_MAX__
#		define SPRIG_WAVE_MACROS_29(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __FLT_MAX__)
#	else
#		define SPRIG_WAVE_MACROS_29(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __FLT_MAX__)
#	endif
#	ifdef __FLT_MIN_EXP__
#		define SPRIG_WAVE_MACROS_30(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __FLT_MIN_EXP__)
#	else
#		define SPRIG_WAVE_MACROS_30(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __FLT_MIN_EXP__)
#	endif
#	ifdef __FLT_MAX_EXP__
#		define SPRIG_WAVE_MACROS_31(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __FLT_MAX_EXP__)
#	else
#		define SPRIG_WAVE_MACROS_31(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __FLT_MAX_EXP__)
#	endif
#	ifdef __FLT_MIN_10_EXP__
#		define SPRIG_WAVE_MACROS_32(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __FLT_MIN_10_EXP__)
#	else
#		define SPRIG_WAVE_MACROS_32(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __FLT_MIN_10_EXP__)
#	endif
#	ifdef __FLT_MAX_10_EXP__
#		define SPRIG_WAVE_MACROS_33(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __FLT_MAX_10_EXP__)
#	else
#		define SPRIG_WAVE_MACROS_33(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __FLT_MAX_10_EXP__)
#	endif
#	ifdef __FLT_HAS_INFINITY__
#		define SPRIG_WAVE_MACROS_34(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __FLT_HAS_INFINITY__)
#	else
#		define SPRIG_WAVE_MACROS_34(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __FLT_HAS_INFINITY__)
#	endif
#	ifdef __FLT_HAS_QUIET_NAN__
#		define SPRIG_WAVE_MACROS_35(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __FLT_HAS_QUIET_NAN__)
#	else
#		define SPRIG_WAVE_MACROS_35(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __FLT_HAS_QUIET_NAN__)
#	endif
#	ifdef __FLT_EPSILON__
#		define SPRIG_WAVE_MACROS_36(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __FLT_EPSILON__)
#	else
#		define SPRIG_WAVE_MACROS_36(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __FLT_EPSILON__)
#	endif
#	ifdef __FLT_MANT_DIG__
#		define SPRIG_WAVE_MACROS_37(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __FLT_MANT_DIG__)
#	else
#		define SPRIG_WAVE_MACROS_37(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __FLT_MANT_DIG__)
#	endif
#	ifdef __FLT_DENORM_MIN__
#		define SPRIG_WAVE_MACROS_38(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __FLT_DENORM_MIN__)
#	else
#		define SPRIG_WAVE_MACROS_38(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __FLT_DENORM_MIN__)
#	endif
#	ifdef __FLT_RADIX__
#		define SPRIG_WAVE_MACROS_39(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __FLT_RADIX__)
#	else
#		define SPRIG_WAVE_MACROS_39(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __FLT_RADIX__)
#	endif
#	ifdef __FLT_EVAL_METHOD__
#		define SPRIG_WAVE_MACROS_40(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __FLT_EVAL_METHOD__)
#	else
#		define SPRIG_WAVE_MACROS_40(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __FLT_EVAL_METHOD__)
#	endif
#	define SPRIG_WAVE_MACROS_41(OPT) SPRIG_WAVE_MACROS_REM(OPT, "float �̐ݒ�")

#	define SPRIG_WAVE_MACROS_42(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef __DBL_DIG__
#		define SPRIG_WAVE_MACROS_43(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __DBL_DIG__)
#	else
#		define SPRIG_WAVE_MACROS_43(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __DBL_DIG__)
#	endif
#	ifdef __DBL_MIN__
#		define SPRIG_WAVE_MACROS_44(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __DBL_MIN__)
#	else
#		define SPRIG_WAVE_MACROS_44(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __DBL_MIN__)
#	endif
#	ifdef __DBL_MAX__
#		define SPRIG_WAVE_MACROS_45(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __DBL_MAX__)
#	else
#		define SPRIG_WAVE_MACROS_45(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __DBL_MAX__)
#	endif
#	ifdef __DBL_MIN_EXP__
#		define SPRIG_WAVE_MACROS_46(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __DBL_MIN_EXP__)
#	else
#		define SPRIG_WAVE_MACROS_46(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __DBL_MIN_EXP__)
#	endif
#	ifdef __DBL_MAX_EXP__
#		define SPRIG_WAVE_MACROS_47(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __DBL_MAX_EXP__)
#	else
#		define SPRIG_WAVE_MACROS_47(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __DBL_MAX_EXP__)
#	endif
#	ifdef __DBL_MIN_10_EXP__
#		define SPRIG_WAVE_MACROS_48(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __DBL_MIN_10_EXP__)
#	else
#		define SPRIG_WAVE_MACROS_48(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __DBL_MIN_10_EXP__)
#	endif
#	ifdef __DBL_MAX_10_EXP__
#		define SPRIG_WAVE_MACROS_49(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __DBL_MAX_10_EXP__)
#	else
#		define SPRIG_WAVE_MACROS_49(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __DBL_MAX_10_EXP__)
#	endif
#	ifdef __DBL_HAS_INFINITY__
#		define SPRIG_WAVE_MACROS_50(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __DBL_HAS_INFINITY__)
#	else
#		define SPRIG_WAVE_MACROS_50(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __DBL_HAS_INFINITY__)
#	endif
#	ifdef __DBL_HAS_QUIET_NAN__
#		define SPRIG_WAVE_MACROS_51(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __DBL_HAS_QUIET_NAN__)
#	else
#		define SPRIG_WAVE_MACROS_51(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __DBL_HAS_QUIET_NAN__)
#	endif
#	ifdef __DBL_EPSILON__
#		define SPRIG_WAVE_MACROS_52(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __DBL_EPSILON__)
#	else
#		define SPRIG_WAVE_MACROS_52(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __DBL_EPSILON__)
#	endif
#	ifdef __DBL_MANT_DIG__
#		define SPRIG_WAVE_MACROS_53(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __DBL_MANT_DIG__)
#	else
#		define SPRIG_WAVE_MACROS_53(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __DBL_MANT_DIG__)
#	endif
#	ifdef __DBL_DENORM_MIN__
#		define SPRIG_WAVE_MACROS_54(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __DBL_DENORM_MIN__)
#	else
#		define SPRIG_WAVE_MACROS_54(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __DBL_DENORM_MIN__)
#	endif
#	define SPRIG_WAVE_MACROS_55(OPT) SPRIG_WAVE_MACROS_REM(OPT, "double �̐ݒ�")

#	define SPRIG_WAVE_MACROS_56(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef __LDBL_DIG__
#		define SPRIG_WAVE_MACROS_57(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __LDBL_DIG__)
#	else
#		define SPRIG_WAVE_MACROS_57(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __LDBL_DIG__)
#	endif
#	ifdef __LDBL_MIN__
#		define SPRIG_WAVE_MACROS_58(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __LDBL_MIN__)
#	else
#		define SPRIG_WAVE_MACROS_58(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __LDBL_MIN__)
#	endif
#	ifdef __LDBL_MAX__
#		define SPRIG_WAVE_MACROS_59(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __LDBL_MAX__)
#	else
#		define SPRIG_WAVE_MACROS_59(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __LDBL_MAX__)
#	endif
#	ifdef __LDBL_MIN_EXP__
#		define SPRIG_WAVE_MACROS_60(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __LDBL_MIN_EXP__)
#	else
#		define SPRIG_WAVE_MACROS_60(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __LDBL_MIN_EXP__)
#	endif
#	ifdef __LDBL_MAX_EXP__
#		define SPRIG_WAVE_MACROS_61(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __LDBL_MAX_EXP__)
#	else
#		define SPRIG_WAVE_MACROS_61(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __LDBL_MAX_EXP__)
#	endif
#	ifdef __LDBL_MIN_10_EXP__
#		define SPRIG_WAVE_MACROS_62(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __LDBL_MIN_10_EXP__)
#	else
#		define SPRIG_WAVE_MACROS_62(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __LDBL_MIN_10_EXP__)
#	endif
#	ifdef __LDBL_MAX_10_EXP__
#		define SPRIG_WAVE_MACROS_63(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __LDBL_MAX_10_EXP__)
#	else
#		define SPRIG_WAVE_MACROS_63(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __LDBL_MAX_10_EXP__)
#	endif
#	ifdef __LDBL_HAS_INFINITY__
#		define SPRIG_WAVE_MACROS_64(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __LDBL_HAS_INFINITY__)
#	else
#		define SPRIG_WAVE_MACROS_64(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __LDBL_HAS_INFINITY__)
#	endif
#	ifdef __LDBL_HAS_QUIET_NAN__
#		define SPRIG_WAVE_MACROS_65(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __LDBL_HAS_QUIET_NAN__)
#	else
#		define SPRIG_WAVE_MACROS_65(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __LDBL_HAS_QUIET_NAN__)
#	endif
#	ifdef __LDBL_EPSILON__
#		define SPRIG_WAVE_MACROS_66(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __LDBL_EPSILON__)
#	else
#		define SPRIG_WAVE_MACROS_66(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __LDBL_EPSILON__)
#	endif
#	ifdef __LDBL_MANT_DIG__
#		define SPRIG_WAVE_MACROS_67(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __LDBL_MANT_DIG__)
#	else
#		define SPRIG_WAVE_MACROS_67(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __LDBL_MANT_DIG__)
#	endif
#	ifdef __LDBL_DENORM_MIN__
#		define SPRIG_WAVE_MACROS_68(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __LDBL_DENORM_MIN__)
#	else
#		define SPRIG_WAVE_MACROS_68(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __LDBL_DENORM_MIN__)
#	endif
#	define SPRIG_WAVE_MACROS_69(OPT) SPRIG_WAVE_MACROS_REM(OPT, "long double �̐ݒ�")

#	define SPRIG_WAVE_MACROS_70(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef _cdecl
#		define SPRIG_WAVE_MACROS_71(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, _cdecl)
#	else
#		define SPRIG_WAVE_MACROS_71(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, _cdecl)
#	endif
#	ifdef _stdcall
#		define SPRIG_WAVE_MACROS_72(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, _stdcall)
#	else
#		define SPRIG_WAVE_MACROS_72(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, _stdcall)
#	endif
#	ifdef _fastcall
#		define SPRIG_WAVE_MACROS_73(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, _fastcall)
#	else
#		define SPRIG_WAVE_MACROS_73(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, _fastcall)
#	endif
#	ifdef __cdecl
#		define SPRIG_WAVE_MACROS_74(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __cdecl)
#	else
#		define SPRIG_WAVE_MACROS_74(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __cdecl)
#	endif
#	ifdef __stdcall
#		define SPRIG_WAVE_MACROS_75(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __stdcall)
#	else
#		define SPRIG_WAVE_MACROS_75(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __stdcall)
#	endif
#	ifdef __fastcall
#		define SPRIG_WAVE_MACROS_76(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __fastcall)
#	else
#		define SPRIG_WAVE_MACROS_76(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __fastcall)
#	endif
#	define SPRIG_WAVE_MACROS_77(OPT) SPRIG_WAVE_MACROS_REM(OPT, "�Ăяo���K��")

#	define SPRIG_WAVE_MACROS_78(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef i386
#		define SPRIG_WAVE_MACROS_79(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, i386)
#	else
#		define SPRIG_WAVE_MACROS_79(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, i386)
#	endif
#	ifdef __i386
#		define SPRIG_WAVE_MACROS_80(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __i386)
#	else
#		define SPRIG_WAVE_MACROS_80(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __i386)
#	endif
#	ifdef __i386__
#		define SPRIG_WAVE_MACROS_81(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __i386__)
#	else
#		define SPRIG_WAVE_MACROS_81(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __i386__)
#	endif
#	define SPRIG_WAVE_MACROS_82(OPT) SPRIG_WAVE_MACROS_REM(OPT, "i386")

#	define SPRIG_WAVE_MACROS_83(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef __tune_i686__
#		define SPRIG_WAVE_MACROS_84(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __tune_i686__)
#	else
#		define SPRIG_WAVE_MACROS_84(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __tune_i686__)
#	endif
#	ifdef __tune_pentiumpro__
#		define SPRIG_WAVE_MACROS_85(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __tune_pentiumpro__)
#	else
#		define SPRIG_WAVE_MACROS_85(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __tune_pentiumpro__)
#	endif
#	define SPRIG_WAVE_MACROS_86(OPT) SPRIG_WAVE_MACROS_REM(OPT, "tune")

#	define SPRIG_WAVE_MACROS_87(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef _X86_
#		define SPRIG_WAVE_MACROS_88(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, _X86_)
#	else
#		define SPRIG_WAVE_MACROS_88(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, _X86_)
#	endif
#	define SPRIG_WAVE_MACROS_89(OPT) SPRIG_WAVE_MACROS_REM(OPT, "x86")

#	define SPRIG_WAVE_MACROS_90(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef __STDC_HOSTED__
#		define SPRIG_WAVE_MACROS_91(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __STDC_HOSTED__)
#	else
#		define SPRIG_WAVE_MACROS_91(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __STDC_HOSTED__)
#	endif
#	ifdef __GXX_ABI_VERSION
#		define SPRIG_WAVE_MACROS_92(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __GXX_ABI_VERSION)
#	else
#		define SPRIG_WAVE_MACROS_92(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __GXX_ABI_VERSION)
#	endif
#	ifdef __DECIMAL_DIG__
#		define SPRIG_WAVE_MACROS_93(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __DECIMAL_DIG__)
#	else
#		define SPRIG_WAVE_MACROS_93(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __DECIMAL_DIG__)
#	endif
#	ifdef __REGISTER_PREFIX__
#		define SPRIG_WAVE_MACROS_94(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __REGISTER_PREFIX__)
#	else
#		define SPRIG_WAVE_MACROS_94(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __REGISTER_PREFIX__)
#	endif
#	ifdef __USER_LABEL_PREFIX__
#		define SPRIG_WAVE_MACROS_95(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __USER_LABEL_PREFIX__)
#	else
#		define SPRIG_WAVE_MACROS_95(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __USER_LABEL_PREFIX__)
#	endif
#	define SPRIG_WAVE_MACROS_96(OPT) SPRIG_WAVE_MACROS_REM(OPT, "���̑���`")

#	define SPRIG_WAVE_MACROS_97(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef __NO_INLINE__
#		define SPRIG_WAVE_MACROS_98(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __NO_INLINE__)
#	else
#		define SPRIG_WAVE_MACROS_98(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __NO_INLINE__)
#	endif
#	ifdef __USING_SJLJ_EXCEPTIONS__
#		define SPRIG_WAVE_MACROS_99(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __USING_SJLJ_EXCEPTIONS__)
#	else
#		define SPRIG_WAVE_MACROS_99(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __USING_SJLJ_EXCEPTIONS__)
#	endif
#	ifdef __FINITE_MATH_ONLY__
#		define SPRIG_WAVE_MACROS_100(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __FINITE_MATH_ONLY__)
#	else
#		define SPRIG_WAVE_MACROS_100(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __FINITE_MATH_ONLY__)
#	endif
#	define SPRIG_WAVE_MACROS_101(OPT) SPRIG_WAVE_MACROS_REM(OPT, "���̑��I�v�V����")

#	define SPRIG_WAVE_MACROS_102(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef __declspec
#		define SPRIG_WAVE_MACROS_103(OPT) SPRIG_WAVE_MACROS_DEFF(OPT, __declspec(x), __attribute__((x)))
#	else
#		define SPRIG_WAVE_MACROS_103(OPT) SPRIG_WAVE_MACROS_NDEFF(OPT, __declspec(x), __attribute__((x)))
#	endif
#	define SPRIG_WAVE_MACROS_104(OPT) SPRIG_WAVE_MACROS_REM(OPT, "����")

#	define SPRIG_WAVE_MACROS_105(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef __CYGWIN__
#		define SPRIG_WAVE_MACROS_106(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __CYGWIN__)
#	else
#		define SPRIG_WAVE_MACROS_106(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __CYGWIN__)
#	endif
#	ifdef __CYGWIN32__
#		define SPRIG_WAVE_MACROS_107(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __CYGWIN32__)
#	else
#		define SPRIG_WAVE_MACROS_107(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __CYGWIN32__)
#	endif
#	define SPRIG_WAVE_MACROS_108(OPT) SPRIG_WAVE_MACROS_REM(OPT, "Cygwin")

#	define SPRIG_WAVE_MACROS_109(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef unix
#		define SPRIG_WAVE_MACROS_110(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, unix)
#	else
#		define SPRIG_WAVE_MACROS_110(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, unix)
#	endif
#	ifdef __unix
#		define SPRIG_WAVE_MACROS_111(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __unix)
#	else
#		define SPRIG_WAVE_MACROS_111(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __unix)
#	endif
#	ifdef __unix__
#		define SPRIG_WAVE_MACROS_112(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __unix__)
#	else
#		define SPRIG_WAVE_MACROS_112(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __unix__)
#	endif
#	define SPRIG_WAVE_MACROS_113(OPT) SPRIG_WAVE_MACROS_REM(OPT, "Unix")

#	define SPRIG_WAVE_MACROS_114(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef __MINGW32__
#		define SPRIG_WAVE_MACROS_115(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __MINGW32__)
#	else
#		define SPRIG_WAVE_MACROS_115(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __MINGW32__)
#	endif
#	define SPRIG_WAVE_MACROS_116(OPT) SPRIG_WAVE_MACROS_REM(OPT, "MinGW")

#	define SPRIG_WAVE_MACROS_117(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef WIN32
#		define SPRIG_WAVE_MACROS_118(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, WIN32)
#	else
#		define SPRIG_WAVE_MACROS_118(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, WIN32)
#	endif
#	ifdef _WIN32
#		define SPRIG_WAVE_MACROS_119(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, _WIN32)
#	else
#		define SPRIG_WAVE_MACROS_119(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, _WIN32)
#	endif
#	ifdef __WIN32
#		define SPRIG_WAVE_MACROS_120(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __WIN32)
#	else
#		define SPRIG_WAVE_MACROS_120(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __WIN32)
#	endif
#	ifdef __WIN32__
#		define SPRIG_WAVE_MACROS_121(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __WIN32__)
#	else
#		define SPRIG_WAVE_MACROS_121(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __WIN32__)
#	endif
#	define SPRIG_WAVE_MACROS_122(OPT) SPRIG_WAVE_MACROS_REM(OPT, "Win32")

#	define SPRIG_WAVE_MACROS_123(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef __MSVCRT__
#		define SPRIG_WAVE_MACROS_124(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, __MSVCRT__)
#	else
#		define SPRIG_WAVE_MACROS_124(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, __MSVCRT__)
#	endif
#	define SPRIG_WAVE_MACROS_125(OPT) SPRIG_WAVE_MACROS_REM(OPT, "MSVCRT")

#	define SPRIG_WAVE_MACROS_126(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")

#	ifdef WINNT
#		define SPRIG_WAVE_MACROS_127(OPT) SPRIG_WAVE_MACROS_DEFV(OPT, WINNT)
#	else
#		define SPRIG_WAVE_MACROS_127(OPT) SPRIG_WAVE_MACROS_NDEFV(OPT, WINNT)
#	endif
#	define SPRIG_WAVE_MACROS_128(OPT) SPRIG_WAVE_MACROS_REM(OPT, "WinNT")

#	define SPRIG_WAVE_MACROS_129(OPT) SPRIG_WAVE_MACROS_SEP(OPT, "-")
	//
	// SPRIG_WAVE_MACROS_NUM
	//
#	define SPRIG_WAVE_MACROS_NUM 130

#endif	// #ifdef SPRIG_WAVE_GCC

#endif	// #ifndef SPRIG_WAVE_COMPILER_GCC_HPP