"use client";

import { z } from "zod";
import { zodResolver } from "@hookform/resolvers/zod";
import { useForm } from "react-hook-form";

import { toast } from "react-toastify";

import { useDeviceStore } from "@/hooks/device-store";
import { CheckIcon } from "@phosphor-icons/react/dist/ssr";

const schema = z.object({
  deviceCode: z
    .string()
    .min(8, "Mínimo de 8 caracteres")
    .max(8, "Máximo de 8 caracteres")
    .regex(/^[A-Z0-9-]+$/, "Apenas letras, números e hífen")
    .toUpperCase()
    .trim(),
});

type FormData = z.infer<typeof schema>;

export default function CodeForm() {
  const form = useForm<FormData>({
    resolver: zodResolver(schema),
    defaultValues: { deviceCode: "" },
  });

  const { deviceCode, setDeviceCode } = useDeviceStore();

  const onSubmit = (data: FormData) => {
    setDeviceCode(data.deviceCode);
    form.reset();
    toast.success("Código salvo com sucesso!");
  };

  return (
    <form
      onSubmit={form.handleSubmit(onSubmit)}
      className="flex justify-center items-start w-full gap-2"
    >
      <div className="w-full">
        <input
          id="deviceCode"
          type="text"
          placeholder="INSIRA O CÓDIGO AQUI"
          className="bg-gray-700 border border-gray-600 text-white text-sm rounded-lg focus:ring-cyan-500 focus:border-cyan-500 block w-full p-2.5 uppercase placeholder-gray-400"
          aria-invalid={!!form.formState.errors.deviceCode || undefined}
          {...form.register("deviceCode")}
        />
        <p className="mt-2 ml-3 text-xs text-gray-300 text-left">
          Seu código atual é:{" "}
          <span className="font-semibold text-cyan-400">{deviceCode}</span>
        </p>
      </div>

      {form.formState.errors.deviceCode && (
        <p className="text-sm text-red-400">
          {form.formState.errors.deviceCode.message}
        </p>
      )}

      <button
        type="submit"
        className="rounded-lg bg-cyan-600 hover:bg-cyan-700 text-white disabled:opacity-60 w-fit p-[0.575rem] flex justify-center items-center hover:scale-105 transition-transform cursor-pointer"
      >
        <CheckIcon size={24} />
      </button>
    </form>
  );
}
