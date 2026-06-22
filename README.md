# 🚀 sunyong Language Compiler System

LLVM 14 컴파일러 인프라를 활용하여 명령형 및 함수형 패러다임을 통합 설계한 독립 사용자 정의 언어 "sunyong"의 공식 컴파일러 아키텍처 저장소입니다.

본 프로젝트는 추상 구문 트리(AST) 분석을 거쳐 호스트 하드웨어 시스템에 최적화된 중간 표현(LLVM IR)을 실시간으로 도출하고, 네이티브 기계어 목적 파일(`.o`)까지 영구 배출하는 정적 컴파일 파이프라인(Static Compiler Pipeline)을 완벽하게 실증합니다.

---

## 💡 언어 핵심 개요 (Language Overview)

* **부동소수점 단일 타입 아키텍처:** 모든 내부 리터럴, 수식, 파라미터는 LLVM 내장 `Type::getDoubleTy()` 엔진 기반의 실수형(`double`) 단일 아키텍처로 일체화되어 처리됩니다.
* **하이브리드 패러다임 제어:** 명령형 제어 흐름 구조인 지역 변수 스택 선언(`var..in`), 반복 제어(`for..in`) 문법을 포함하면서도, 모든 제어문 자체가 최종 계산값을 반환하는 함수형 수식(Expression) 형태로 결합되어 있습니다.
* **동적 확장성:** 사용자가 런타임 세션에서 직접 우선순위(Precedence) 가중치를 부여할 수 있는 사용자 정의 단항/이항 연산자 확장 매커니즘을 온전히 지원합니다.

---

## 📝 구문 규칙 명세 (EBNF Specification)

**sunyong** 프로그래밍 언어의 모든 문법적 유효성과 컴파일 규칙은 표준 Extended Backus-Naur Form(EBNF) 기법에 의거하여 다음과 같이 엄밀하게 정의됩니다.

```ebnf
(* sunyong Language EBNF Grammar Specification *)

(* 최상위 구조 제어 *)
TopLevel        ::= Definition | Extern | Expression ;

(* 함수 정의 및 외부 선언 *)
Definition      ::= "def" Prototype Expression ";" ;
Extern          ::= "extern" Prototype ";" ;

(* 프로토타입 체계 (일반 함수, 단항 연산자, 이항 연산자 확장 명세) *)
Prototype       ::= Identifier "(" [ IdList ] ")"
                  | "unary" operator "(" Identifier ")"
                  | "binary" operator [ Number ] "(" Identifier Identifier ")" ;
IdList          ::= Identifier { "," Identifier } ;

(* 표현식 파이프라인 *)
Expression      ::= PrimaryExpr { binary_op PrimaryExpr } ;
PrimaryExpr     ::= NumberExpr
                  | VariableExpr
                  | CallExpr
                  | IfExpr
                  | ForExpr
                  | VarExpr
                  | ParenExpr ;

(* 세부 제어 구문 및 블록 스코프 명세 *)
ParenExpr       ::= "(" Expression ")" ;
NumberExpr      ::= Number ;
VariableExpr    ::= Identifier ;
CallExpr        ::= Identifier "(" [ ExprList ] ")" ;
ExprList        ::= Expression { "," Expression } ;
IfExpr          ::= "if" Expression "then" Expression "else" Expression ;
ForExpr         ::= "for" Identifier "=" Expression "," Expression [ "," Expression ] "in" Expression ;
VarExpr         ::= "var" Identifier [ "=" Expression ] { "," Identifier [ "=" Expression ] } "in" Expression ;

(* 최소 단위 어휘 규칙 (Lexical Rules) *)
Identifier      ::= letter { letter | digit } ;
Number          ::= digit { digit } [ "." { digit } ] ;
letter          ::= "a" | ... | "z" | "A" | ... | "Z" ;
digit           ::= "0" | "1" | ... | "9" ;
operator        ::= "+" | "-" | "*" | "<" | "=" | ":" | "@" | "|" ;
