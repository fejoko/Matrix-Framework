#ifndef ___MTRX___APPLICATION_H
#define ___MTRX___APPLICATION_H

typedef struct Matrix_Application Matrix_Application;
typedef struct Matrix_Application_Core Matrix_Application_Core;
typedef struct Matrix_Application_Info Matrix_Application_Info;
typedef struct Matrix_Application_Settings Matrix_Application_Settings;

void matrix_application_attach(Matrix_Application* const application); //defined by client

Matrix_Application_Core matrix_application_core_construct();
void matrix_application_core_destruct(Matrix_Application_Core* const application_core);

Matrix_Application_Info matrix_application_info_construct();
void matrix_application_info_destruct(Matrix_Application_Info* const application_info);

Matrix_Application_Settings matrix_application_settings_construct();
void matrix_application_settings_destruct(Matrix_Application_Settings* const application_settings);

void matrix_application_core_set(const Matrix_Application_Core application_core, Matrix_Application* const application);
void matrix_application_info_set(const Matrix_Application_Info application_info, Matrix_Application* const application);
void matrix_application_settings_set(const Matrix_Application_Settings application_settings, Matrix_Application* const application);

void* matrix_application_data_get(const Matrix_Application* const application);

const char* matrix_application_path_abs_get(const Matrix_Application* const application);

#endif // !___MTRX___APPLICATION_H