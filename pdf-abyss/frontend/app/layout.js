import "./globals.css";
import Nav from "../components/Nav";

export const metadata = {
  title: "PDF Abyss - Free student PDF library",
  description: "Upload, scan, categorize and download PDFs safely and for free.",
};

export const viewport = { width: "device-width", initialScale: 1 };

export default function RootLayout({ children }) {
  return (
    <html lang="en">
      <body>
        <header className="header">
          <div className="header-inner">
            <a href="/" className="brand">PDF <span>Abyss</span></a>
            <Nav />
          </div>
        </header>
        <main>{children}</main>
        <footer className="footer">PDF Abyss &middot; Free &amp; safe PDF sharing &middot; Every upload is virus-scanned</footer>
      </body>
    </html>
  );
}
