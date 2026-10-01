"use client";

import { useEffect, useState } from "react";
import { API_URL } from "../../lib/api";

export default function UploadPage() {
  const [token, setToken] = useState("");
  const [title, setTitle] = useState("");
  const [description, setDescription] = useState("");
  const [file, setFile] = useState(null);
  const [categories, setCategories] = useState([]);
  const [suggestedCategory, setSuggestedCategory] = useState("");
  const [documentType, setDocumentType] = useState("");
  const [institution, setInstitution] = useState("");
  const [year, setYear] = useState("");
  const [license, setLicense] = useState("");
  const [message, setMessage] = useState("");
  const [ok, setOk] = useState(false);
  const [busy, setBusy] = useState(false);

  useEffect(() => {
    try {
      setToken(localStorage.getItem("token") || "");
    } catch {}
    fetch(`${API_URL}/categories`)
      .then((r) => (r.ok ? r.json() : []))
      .then((d) => setCategories(Array.isArray(d) ? d : []))
      .catch(() => setCategories([]));
  }, []);

  async function submit(e) {
    e.preventDefault();
    setMessage("");
    setOk(false);
    if (!token) return setMessage("Please login first.");
    if (!file) return setMessage("Please choose a PDF file.");

    const fd = new FormData();
    fd.append("file", file);
    fd.append("title", title);
    if (description) fd.append("description", description);
    if (suggestedCategory) fd.append("suggested_category", suggestedCategory);
    if (documentType) fd.append("document_type", documentType);
    if (institution) fd.append("institution", institution);
    if (year) fd.append("year", year);
    if (license) fd.append("license", license);

    setBusy(true);
    try {
      const res = await fetch(`${API_URL}/files`, {
        method: "POST",
        headers: { Authorization: `Bearer ${token}` },
        body: fd,
      });
      if (res.status === 401) {
        localStorage.removeItem("token");
        setToken("");
        return setMessage("Session expired. Please login again.");
      }
      if (!res.ok) {
        return setMessage(`Upload failed: ${await res.text()}`);
      }
      setOk(true);
      setMessage("Upload received. Your PDF is being scanned and will appear once approved.");
      setTitle(""); setDescription(""); setFile(null); e.target.reset();
    } catch {
      setMessage("Cannot reach the server. Check NEXT_PUBLIC_API_URL and that the backend is running.");
    } finally {
      setBusy(false);
    }
  }

  return (
    <div className="panel form" style={{ maxWidth: 640 }}>
      <h1>Upload a PDF</h1>
      <p className="sub">Files are quarantined and virus-scanned before they go public.</p>
      {!token && (
        <div className="msg">Please <a href="/login">login</a> or <a href="/register">register</a> before uploading.</div>
      )}
      <form onSubmit={submit} className="form" style={{ maxWidth: "none" }}>
        <input placeholder="Title" value={title} onChange={(e) => setTitle(e.target.value)} required />
        <textarea placeholder="Description" value={description} onChange={(e) => setDescription(e.target.value)} />
        <select value={suggestedCategory} onChange={(e) => setSuggestedCategory(e.target.value)}>
          <option value="">Suggested category (optional)</option>
          {categories.map((c) => (<option key={c.id} value={c.name}>{c.name}</option>))}
        </select>
        <select value={documentType} onChange={(e) => setDocumentType(e.target.value)}>
          <option value="">Document type</option>
          <option>Book</option><option>Past Paper</option><option>Lecture Notes</option>
          <option>Assignment</option><option>Research Paper</option><option>Other</option>
        </select>
        <input placeholder="Institution, e.g. MIT" value={institution} onChange={(e) => setInstitution(e.target.value)} />
        <input placeholder="Year, e.g. 2023" type="number" value={year} onChange={(e) => setYear(e.target.value)} />
        <input placeholder="License, e.g. Creative Commons" value={license} onChange={(e) => setLicense(e.target.value)} />
        <input type="file" accept="application/pdf" onChange={(e) => setFile(e.target.files?.[0] || null)} required />
        <label className="check"><input type="checkbox" required /> I confirm I have the right to share this file.</label>
        <button className="btn" type="submit" disabled={busy}>{busy ? "Uploading..." : "Upload"}</button>
      </form>
      {message && <div className={`msg ${ok ? "good" : "err"}`}>{message}</div>}
    </div>
  );
}
