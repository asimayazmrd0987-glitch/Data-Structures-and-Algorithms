"use client";

import { useState } from "react";
import { API_URL } from "../../lib/api";

export default function RegisterPage() {
  const [fullName, setFullName] = useState("");
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [message, setMessage] = useState("");
  const [ok, setOk] = useState(false);
  const [busy, setBusy] = useState(false);

  async function submit(e) {
    e.preventDefault();
    setMessage("");
    setOk(false);
    setBusy(true);
    try {
      const res = await fetch(`${API_URL}/auth/register`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ email, password, full_name: fullName }),
      });
      if (!res.ok) {
        let detail = `Registration failed (${res.status}).`;
        try {
          const j = await res.json();
          if (typeof j.detail === "string") detail = j.detail;
        } catch {}
        setMessage(detail);
        return;
      }
      setOk(true);
      setMessage("Account created. You can now log in.");
    } catch {
      setMessage("Cannot reach the server. Check NEXT_PUBLIC_API_URL and that the backend is running.");
    } finally {
      setBusy(false);
    }
  }

  return (
    <div className="panel form">
      <h1>Create account</h1>
      <p className="sub">Free forever. Takes ten seconds.</p>
      <form onSubmit={submit} className="form">
        <input placeholder="Full name" value={fullName} onChange={(e) => setFullName(e.target.value)} />
        <input placeholder="Email" type="email" value={email} onChange={(e) => setEmail(e.target.value)} required />
        <input placeholder="Password" type="password" value={password} onChange={(e) => setPassword(e.target.value)} required minLength={8} />
        <button className="btn" type="submit" disabled={busy}>{busy ? "Creating..." : "Register"}</button>
      </form>
      {message && <div className={`msg ${ok ? "good" : "err"}`}>{message}</div>}
      <p className="sub">Already registered? <a href="/login">Login</a></p>
    </div>
  );
}
