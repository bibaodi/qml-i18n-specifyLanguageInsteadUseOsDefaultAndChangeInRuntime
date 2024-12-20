# qml-i18n-specifyLanguageInsteadUseOsDefaultAndChangeInRuntime
- eton@241219

- based on example from qt6 'qml-i18n';

## support two features:
1. specify the local language in app start up, instead of using the setting from OS;
2. suppor user change language in runtime;

## Env:
- Debian12;
- Qt6.5; 

## generate translations
### 1. generate TS files
```sh
cd i18n && lupdate ../qml-i18n.qrc -ts qml_en.ts
```

### 2. confirm translations
this will make 'unfinished' to finished.
```sh
linguist qml_en.ts
```
