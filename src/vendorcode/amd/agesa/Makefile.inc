subdirs-$(CONFIG_CPU_AMD_AGESA_FAMILY12) += f12
subdirs-$(CONFIG_CPU_AMD_AGESA_FAMILY14) += f14
subdirs-$(CONFIG_CPU_AMD_AGESA_FAMILY15) += f15
subdirs-$(CONFIG_CPU_AMD_AGESA_FAMILY15_TN) += f15tn
subdirs-$(CONFIG_CPU_AMD_AGESA_FAMILY16_KB) += f16kb

ifeq ($(CONFIG_CPU_AMD_AGESA),y)

subdirs-y += common

classes-y += libagesa
libagesa-y =
libagesa-generic-ccopts += -D__LIBAGESA__
libagesa-generic-ccopts += $(AGESA_INC) $(AGESA_AUTOINCLUDES)

ifeq ($(CONFIG_ARCH_ROMSTAGE_X86_32),y)
$(eval $(call create_class_compiler,libagesa,x86_32))
else
$(eval $(call create_class_compiler,libagesa,x86_64))
endif

# buildOpts should be in libagesa
$(obj)/romstage/mainboard/$(MAINBOARDDIR)/buildOpts.o: CPPFLAGS_x86_32 += $(BUILDOPTS_INCLUDES)
$(obj)/ramstage/mainboard/$(MAINBOARDDIR)/buildOpts.o: CPPFLAGS_x86_32 += $(BUILDOPTS_INCLUDES)

$(obj)/romstage/vendorcode/amd/agesa/common/agesa-entry.o: CPPFLAGS_x86_32 += $(BUILDOPTS_INCLUDES)
$(obj)/ramstage/vendorcode/amd/agesa/common/agesa-entry.o: CPPFLAGS_x86_32 += $(BUILDOPTS_INCLUDES)

endif
