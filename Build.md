# 웹에서 빌드하는 방법

일반적인 Readme.md에 작성하면 알아보기 힘들까봐 따로 작성합니다.

참고로 리눅스 기반으로 설명이 진행됩니다!

# 1. `emsdk`설치

일단 emsdk 리포지토리인 [`https://github.com/emscripten-core/emsdk`](https://github.com/emscripten-core/emsdk) 프로젝트 전체를 저장합니다.

그리고 해당 디렉토리에서 아래의 명령어를 진행합니다.

```bash
# Download and install the latest SDK tools.
./emsdk install latest

# Make the "latest" SDK "active" for the current user. (writes .emscripten file)
./emsdk activate latest

# Activate PATH and other environment variables in the current terminal
source ./emsdk_env.sh
```

여기까지 진행하면 프로젝트 폴더가 PATH 경로에도 추가되어 사용할 수 있게 됩니다.

만약 추가되지 않았다면 재부팅을 해보시는 것을 추천드립니다.

# 2. 해당 프로젝트 가져오기

```bash
git clone https://github.com/Moyodao/AvatarRenderer.git
```
`git`명령어를 사용하거나 다른 소스관리툴을 이용하여 이 프로젝트를 클론 시킵니다.

# 3. 빌드 스크립트 실행

```bash
./build_env.sh
```
`platforms/Web` 폴더에 해당 스크립트가 존재합니다.

해당 폴더로 들어가서 위와 같이 스크립트를 실행하면 자동으로 빌드하기 시작합니다.

### 빌드 스크립트 내 진행 순서

1. 엔진의 서브모듈을 다운받거나 새로 풀을 받게 됩니다.
2. build 폴더를 생성하여 해당 폴더에 빌드에 필요한 파일들을 생성하게 됩니다.
3. `Assets`폴더에 있는 모든 에셋을 zip으로 압축시켜 build 폴더에 넣습니다.
4. 본격적으로 빌드를 합니다.
5. 빌드 후 나온 결과물은 build폴더 내 `result`에 생성됩니다.

### 스크립트 파일 설명

* `build_env.sh` : emsdk가 PATH경로에 등록되어 바로 호출 가능한 환경에서 작동하는 스크립트입니다. (기본값)
* `build.sh` : emsdk의 경로가 build폴더 기준 `../../../../emsdk`에 위치했을 때 작동하는 스크립트입니다.

# 4. 빌드 된 결과물 확인

빌드 된 결과물은 `platforms/Web/build/result`에 저장되어있습니다.

웹 상에 정상적으로 나타나는지 확인을 위해서는 해당 result 경로에서 아래의 명령어로 간단한 http 서버를 열어주면 됩니다.

```bash
python3 -m http.server [포트]
```
포트 기본값은 80입니다. 

## 번외. 어디까지가 개발환경의 완성인가요?

위 빌드 진행 상황 중 2번이 끝나면 개발환경이 **거의** 완성됩니다.

하지만 `git clone`할 때 따로 특정 옵션을 주지 않았다면 게임 엔진 서브모듈이 빠져있습니다.</br>
따라서 해당 프로젝트 아무 경로나 터미널을 열고 아래와 같이 서브모듈을 pull 하시면 됩니다.

```bash
git submodule update --init --recursive --remote
```

> 만약 엔진이 업데이트되어 서브모듈을 업데이트 해야한다면 위 명령어 그대로 사용하셔도 괜찮습니다.</br>
> 그리고 서브모듈은 `git pull`같은 명령어로 자동으로 업데이트가 되지 않기 때문에 수동으로 해야하는 점 참고 바랍니다!

그리고 서브모듈의 소스를 수정하는건 실제 엔진에 적용도 되지 않을 뿐 더러</br>
dirty상태가 되어 정상적인 서브모듈 업데이트가 힘듭니다ㅠ

따라서 엔진 소스코드(서브모듈)의 직접적인 수정은 추천드리지 않습니다ㅠ
