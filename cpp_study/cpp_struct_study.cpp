/*
 * C++ struct study notes
 *
 * 목적:
 * - 회사 코드 내용을 노출하지 않고, 우리가 공부한 "구조체/생성자/초기화/객체/namespace/배열"
 *   문법을 순수 예제 코드로 정리한 파일입니다.
 * - 실제 프로젝트 로직이 아니라, 문법 패턴을 이해하기 위한 작은 예제입니다.
 *
 * 컴파일 예시:
 *   g++ -std=c++17 cpp_struct_study.cpp -o cpp_struct_study
 *
 * 실행 예시:
 *   ./cpp_struct_study
 *   ./cpp_struct_study --help
 */

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// 1. namespace와 :: 연산자
// ---------------------------------------------------------------------------
//
// namespace는 이름을 담는 공간입니다.
//
// 같은 이름의 클래스/함수/변수가 여러 곳에 있어도 충돌하지 않게 묶어줍니다.
// 예를 들어 아래 KEY는 그냥 KEY가 아니라:
//
//   study_mode::LaserTargetMode::KEY
//
// 라는 전체 이름을 가집니다.
//
// 여기서 :: 는 "그 안에 있는 것"을 꺼낼 때 쓰는 범위 지정 연산자입니다.
namespace study_mode {
struct LaserTargetMode {
    // static:
    // - 객체를 만들지 않아도 타입 이름으로 바로 접근할 수 있게 합니다.
    //
    // constexpr:
    // - 컴파일 시점에 정해지는 상수라는 뜻입니다.
    //
    // const char*:
    // - C 스타일 문자열입니다.
    //
    // 이 값은 "이 설정은 어떤 감지 방식을 쓸 것인가?"를 나타내는 문자열 key라고 보면 됩니다.
    static constexpr const char* KEY = "laser-target-mode";
};
} // namespace study_mode

// ---------------------------------------------------------------------------
// 2. 구조체 struct란?
// ---------------------------------------------------------------------------
//
// struct는 여러 변수를 하나의 묶음으로 만든 사용자 정의 타입입니다.
//
// int, float, std::string은 C++에 이미 있는 타입입니다.
// 그런데 프로그램을 만들다 보면 "설정값 묶음", "사람 정보", "로봇 상태"처럼
// 여러 값을 한 덩어리로 들고 다니고 싶을 때가 있습니다.
//
// 그때 struct를 만듭니다.
//
// 예:
//   PIDParams pid;
//
// 라고 쓰면 pid 안에는 p, i, d, minValue, maxValue 같은 값들이 함께 들어 있습니다.
struct PIDParams {
    float p;
    float i;
    float d;
    float integralMax;
    float minValue;
    float maxValue;
    float accelerationGain;

    // 생성자 constructor:
    // - 객체가 만들어질 때 자동으로 호출되는 함수입니다.
    // - 이름이 struct 이름과 같습니다.
    //
    // 예:
    //   PIDParams pid(1.0f, 0.0f, 0.1f, 0.2f, 0.0f, 1.0f, 0.5f);
    //
    // 이렇게 만들면 아래 생성자가 호출됩니다.
    PIDParams(float pValue = 0.0f,
              float iValue = 0.0f,
              float dValue = 0.0f,
              float integralMaxValue = 0.0f,
              float minValue = 0.0f,
              float maxValue = 0.0f,
              float accelerationGainValue = 0.0f)
        // 콜론 뒤에 있는 부분을 "멤버 초기화 리스트"라고 합니다.
        //
        // 객체가 만들어지는 순간 멤버 변수에 값을 넣습니다.
        //
        // 왼쪽 p는 이 구조체의 멤버 변수 p입니다.
        // 오른쪽 pValue는 생성자 매개변수입니다.
        : p(pValue),
          i(iValue),
          d(dValue),
          integralMax(integralMaxValue),
          minValue(minValue),
          maxValue(maxValue),
          accelerationGain(accelerationGainValue)
    {
        // 중괄호 안은 "생성자 본문"입니다.
        //
        // 여기에는 단순 초기화보다는 조건 검사, 값 보정, 로그 출력 같은 코드를 넣는 경우가 많습니다.
        //
        // 예: accelerationGain이 너무 크면 1.0으로 제한합니다.
        if (accelerationGain > 1.0f) {
            accelerationGain = 1.0f;
        }
    }
};

// ---------------------------------------------------------------------------
// 3. struct 안에 struct/vector/string/bool/int/float을 넣을 수 있다
// ---------------------------------------------------------------------------
//
// 아래 StudyParams는 "어떤 장치를 제어하기 위한 설정값 묶음"이라는 가상의 예제입니다.
// 실제 회사 코드가 아니라, 우리가 본 패턴을 공부용으로 단순화한 것입니다.
struct DetectionOption {
    std::string modelName;
    float matchingScoreThreshold;
    float covarianceLow;
    float covarianceHigh;
};

struct StudyParams {
    // 생성자:
    // - StudyParams 객체를 만들 때 modeName을 받을 수 있습니다.
    // - = "" 는 기본값입니다. 아무 값도 안 넣으면 빈 문자열이 들어갑니다.
    //
    // 예:
    //   StudyParams a;                       // modeName 기본값 ""
    //   StudyParams b("laser-target-mode");  // modeName에 문자열 전달
    StudyParams(const std::string& modeName = "")
        // 앞쪽 초기화:
        // - bool, string처럼 생성되는 순간 바로 값을 넣기 좋은 멤버를 초기화합니다.
        // - modeName(modeName)은 이름이 같아서 헷갈릴 수 있습니다.
        //   왼쪽 modeName  = 구조체 멤버 변수
        //   오른쪽 modeName = 생성자 매개변수
        : enableCommand(false),
          allowReplanning(false),
          modeName(modeName)
    {
        // 뒤쪽 중괄호 초기화/대입:
        // - 객체가 만들어진 뒤, 생성자 본문에서 값을 대입합니다.
        //
        // 아래처럼 여러 변수에 같은 값을 한 번에 넣을 수도 있습니다.
        // 오른쪽부터 계산됩니다.
        //
        //   direction = finishCondition = originType = 0;
        //
        // 뜻:
        //   originType = 0;
        //   finishCondition = originType;
        //   direction = finishCondition;
        direction = finishCondition = originType = 0;

        xOffset = pathLength = goalThreshold = 0.0f;
        robotWidth = robotHeight = safetyWidth = safetyHeight = 0.0f;
    }

    // 여기부터는 "멤버 변수 선언"입니다.
    //
    // 위 생성자에서 enableCommand(false)라고 썼다고 해서 변수가 만들어진 것이 아닙니다.
    // 실제 변수는 아래 줄에서 선언됩니다.
    //
    // 생성자는 아래에 선언된 멤버 변수들에게 "처음 값을 뭘로 넣을지" 알려주는 함수입니다.
    std::vector<DetectionOption> detectionOptions;

    bool enableCommand;
    bool allowReplanning;

    int direction;
    int finishCondition;
    int originType;

    float xOffset;
    std::vector<float> yOffsets;
    float pathLength;
    float goalThreshold;

    PIDParams linearPID;
    PIDParams angularPID;

    std::string modeName;

    float robotWidth;
    float robotHeight;
    float safetyWidth;
    float safetyHeight;
};

// ---------------------------------------------------------------------------
// 4. 함수는 "자동으로" 호출되지 않는다
// ---------------------------------------------------------------------------
//
// --help 자체에 특별한 기능이 있는 것이 아닙니다.
//
// 사용자가 터미널에서:
//
//   ./program --help
//
// 라고 실행하면 운영체제는 문자열 "--help"를 argv 배열에 담아서 main 함수로 넘겨줍니다.
// 그다음 코드가 argv를 검사해서 help() 함수를 직접 호출하는 것입니다.
void printHelp(const char* programName)
{
    std::cout << "Usage: " << programName << " [--help]\n";
    std::cout << "This file is a beginner C++ struct study example.\n";
}

int main(int argc, char** argv)
{
    // argc:
    // - 프로그램 실행 시 들어온 argument 개수입니다.
    //
    // argv:
    // - argument 문자열 배열입니다.
    //
    // 예:
    //   ./cpp_struct_study --help
    //
    // argc == 2
    // argv[0] == "./cpp_struct_study"
    // argv[1] == "--help"
    if (argc > 1 && std::string(argv[1]) == "--help") {
        // --help가 마법처럼 함수를 실행하는 것이 아닙니다.
        // 이 if문이 "--help" 문자열을 보고 printHelp 함수를 호출합니다.
        printHelp(argv[0]);
        return 0;
    }

    // -----------------------------------------------------------------------
    // 5. 객체 만들기
    // -----------------------------------------------------------------------
    //
    // StudyParams params(...):
    // - StudyParams 타입의 params 객체를 만듭니다.
    // - 괄호 안 문자열은 생성자 인자로 들어갑니다.
    //
    // study_mode::LaserTargetMode::KEY:
    // - study_mode namespace 안의
    // - LaserTargetMode struct 안의
    // - static 상수 KEY를 가져오는 문법입니다.
    StudyParams params(study_mode::LaserTargetMode::KEY);

    // 점 연산자 . :
    // - 객체 안의 멤버 변수나 멤버 함수에 접근할 때 씁니다.
    params.enableCommand = true;
    params.allowReplanning = false;
    params.direction = 1;

    // -----------------------------------------------------------------------
    // 6. 배열 초기화
    // -----------------------------------------------------------------------
    //
    // float linearValues[7]:
    // - float 값 7개를 담는 C 스타일 배열입니다.
    //
    // {0.0f,}:
    // - 첫 값을 0.0f로 넣고, 나머지도 0으로 초기화합니다.
    //
    // 0.0f:
    // - float 타입 숫자입니다.
    // - 그냥 0.0은 double 타입이고, 0.0f는 float 타입입니다.
    float linearValues[7] = {0.0f,};
    float angularValues[6] = {0.0f,};

    linearValues[0] = 1.2f;  // P gain
    linearValues[1] = 0.0f;  // I gain
    linearValues[2] = 0.1f;  // D gain
    linearValues[3] = 0.2f;  // integral max
    linearValues[4] = 0.0f;  // min output
    linearValues[5] = 0.8f;  // max output
    linearValues[6] = std::min(std::abs(1.5f), 1.0f); // 1.0f로 제한됨

    angularValues[0] = 2.0f;
    angularValues[1] = 0.0f;
    angularValues[2] = 0.2f;
    angularValues[3] = 0.1f;
    angularValues[4] = 0.0f;
    angularValues[5] = 1.0f;

    // 배열에 담긴 값을 PIDParams 구조체 객체로 묶습니다.
    params.linearPID = PIDParams(linearValues[0],
                                 linearValues[1],
                                 linearValues[2],
                                 linearValues[3],
                                 linearValues[4],
                                 linearValues[5],
                                 linearValues[6]);

    params.angularPID = PIDParams(angularValues[0],
                                  angularValues[1],
                                  angularValues[2],
                                  angularValues[3],
                                  angularValues[4],
                                  angularValues[5]);

    // -----------------------------------------------------------------------
    // 7. vector에 구조체 객체 추가하기
    // -----------------------------------------------------------------------
    DetectionOption option;
    option.modelName = "sample-target";
    option.matchingScoreThreshold = 0.7f;
    option.covarianceLow = 0.1f;
    option.covarianceHigh = 0.5f;

    // emplace_back:
    // - vector 끝에 원소를 추가합니다.
    // - 여기서는 DetectionOption 하나를 params.detectionOptions에 넣습니다.
    params.detectionOptions.emplace_back(option);

    // offset 값도 vector에 여러 개 넣을 수 있습니다.
    params.xOffset = -0.05f;
    params.yOffsets.emplace_back(0.10f);
    params.yOffsets.emplace_back(0.20f);

    // -----------------------------------------------------------------------
    // 8. 출력하면서 확인하기
    // -----------------------------------------------------------------------
    std::cout << "modeName: " << params.modeName << '\n';
    std::cout << "enableCommand: " << params.enableCommand << '\n';
    std::cout << "direction: " << params.direction << '\n';
    std::cout << "linear p: " << params.linearPID.p << '\n';
    std::cout << "linear accelerationGain: " << params.linearPID.accelerationGain << '\n';
    std::cout << "detection count: " << params.detectionOptions.size() << '\n';
    std::cout << "first detection model: " << params.detectionOptions[0].modelName << '\n';
    std::cout << "first y offset: " << params.yOffsets[0] << '\n';

    return 0;
}
