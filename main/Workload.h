#pragma once

// Функции для теста vtable
void init_vtable_sensors();
void cleanup_vtable_sensors();
int run_vtable_pass();
int get_vtable_element_size();

// Функции для теста variant
void init_variant_sensors();
void cleanup_variant_sensors();
int run_variant_pass();
int get_variant_element_size();