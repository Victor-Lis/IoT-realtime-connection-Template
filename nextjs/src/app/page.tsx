import BrokerBox from "@/components/broker-box";
import CodeForm from "@/components/code-form";
import ToggleLed from "@/components/toggle-led";

export default function HomePage() {
  return (
    <main className="flex min-h-screen flex-col items-center justify-center bg-gray-900 text-white p-8">
      <div className="w-full max-w-md p-8 space-y-6 bg-gray-800 rounded-xl shadow-lg text-center">
        <h1 className="text-4xl font-extrabold text-cyan-400 mb-4 drop-shadow-lg tracking-wide">
          LED Control
        </h1>

        <BrokerBox />

        <div>
          <CodeForm />
        </div>

        <ToggleLed />
      </div>
    </main>
  );
}
